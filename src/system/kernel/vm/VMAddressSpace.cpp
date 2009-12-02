/*
 * Copyright 2009, Ingo Weinhold, ingo_weinhold@gmx.de.
 * Copyright 2002-2009, Axel Dörfler, axeld@pinc-software.de.
 * Distributed under the terms of the MIT License.
 *
 * Copyright 2001-2002, Travis Geiselbrecht. All rights reserved.
 * Distributed under the terms of the NewOS License.
 */


#include <vm/VMAddressSpace.h>

#include <stdlib.h>

#include <KernelExport.h>

#include <util/OpenHashTable.h>

#include <heap.h>
#include <thread.h>
#include <vm/vm.h>
#include <vm/vm_priv.h>
#include <vm/VMArea.h>


//#define TRACE_VM
#ifdef TRACE_VM
#	define TRACE(x) dprintf x
#else
#	define TRACE(x) ;
#endif


#define ASPACE_HASH_TABLE_SIZE 1024


// #pragma mark - AddressSpaceHashDefinition


struct AddressSpaceHashDefinition {
	typedef team_id			KeyType;
	typedef VMAddressSpace	ValueType;

	size_t HashKey(team_id key) const
	{
		return key;
	}

	size_t Hash(const VMAddressSpace* value) const
	{
		return HashKey(value->ID());
	}

	bool Compare(team_id key, const VMAddressSpace* value) const
	{
		return value->ID() == key;
	}

	VMAddressSpace*& GetLink(VMAddressSpace* value) const
	{
		return value->HashTableLink();
	}
};

typedef BOpenHashTable<AddressSpaceHashDefinition> AddressSpaceTable;

static AddressSpaceTable	sAddressSpaceTable;
static rw_lock				sAddressSpaceTableLock;

VMAddressSpace* VMAddressSpace::sKernelAddressSpace;


// #pragma mark - VMAddressSpace


VMAddressSpace::VMAddressSpace(team_id id, addr_t base, size_t size,
	bool kernel)
	:
	areas(NULL),

	fBase(base),
	fSize(size),
	fID(id),
	fRefCount(1),
	fFaultCount(0),
	fChangeCount(0),
	fAreaHint(NULL),
	fDeleting(false)
{
	rw_lock_init(&fLock, kernel ? "kernel address space" : "address space");
}


VMAddressSpace::~VMAddressSpace()
{
	if (this == sKernelAddressSpace)
		panic("deleting the kernel aspace!\n");

	TRACE(("VMAddressSpace::~VMAddressSpace: called on aspace %" B_PRId32 "\n",
		ID()));

	WriteLock();

	fTranslationMap.ops->destroy(&fTranslationMap);

	rw_lock_destroy(&fLock);
}


/*static*/ status_t
VMAddressSpace::Init()
{
	rw_lock_init(&sAddressSpaceTableLock, "address spaces table");

	// create the area and address space hash tables
	{
		new(&sAddressSpaceTable) AddressSpaceTable;
		status_t error = sAddressSpaceTable.Init(ASPACE_HASH_TABLE_SIZE);
		if (error != B_OK)
			panic("vm_init: error creating aspace hash table\n");
	}

	// create the initial kernel address space
	if (Create(B_SYSTEM_TEAM, KERNEL_BASE, KERNEL_SIZE, true,
			&sKernelAddressSpace) != B_OK) {
		panic("vm_init: error creating kernel address space!\n");
	}

	add_debugger_command("aspaces", &_DumpListCommand,
		"Dump a list of all address spaces");
	add_debugger_command("aspace", &_DumpCommand,
		"Dump info about a particular address space");

	return B_OK;
}


/*static*/ status_t
VMAddressSpace::InitPostSem()
{
	status_t status = arch_vm_translation_map_init_kernel_map_post_sem(
		&sKernelAddressSpace->fTranslationMap);
	if (status != B_OK)
		return status;

	return B_OK;
}


void
VMAddressSpace::Put()
{
	bool remove = false;

	rw_lock_write_lock(&sAddressSpaceTableLock);
	if (atomic_add(&fRefCount, -1) == 1) {
		sAddressSpaceTable.RemoveUnchecked(this);
		remove = true;
	}
	rw_lock_write_unlock(&sAddressSpaceTableLock);

	if (remove)
		delete this;
}


/*! Deletes all areas in the specified address space, and the address
	space by decreasing all reference counters. It also marks the
	address space of being in deletion state, so that no more areas
	can be created in it.
	After this, the address space is not operational anymore, but might
	still be in memory until the last reference has been released.
*/
void
VMAddressSpace::RemoveAndPut()
{
	WriteLock();
	fDeleting = true;
	WriteUnlock();

	vm_delete_areas(this);
	Put();
}


/*static*/ status_t
VMAddressSpace::Create(team_id teamID, addr_t base, size_t size, bool kernel,
	VMAddressSpace** _addressSpace)
{
	VMAddressSpace* addressSpace = new(nogrow) VMAddressSpace(teamID, base,
		size, kernel);
	if (addressSpace == NULL)
		return B_NO_MEMORY;

	TRACE(("vm_create_aspace: team %ld (%skernel): %#lx bytes starting at "
		"%#lx => %p\n", id, kernel ? "!" : "", size, base, addressSpace));

	// initialize the corresponding translation map
	status_t status = arch_vm_translation_map_init_map(
		&addressSpace->fTranslationMap, kernel);
	if (status != B_OK) {
		delete addressSpace;
		return status;
	}

	// add the aspace to the global hash table
	rw_lock_write_lock(&sAddressSpaceTableLock);
	sAddressSpaceTable.InsertUnchecked(addressSpace);
	rw_lock_write_unlock(&sAddressSpaceTableLock);

	*_addressSpace = addressSpace;
	return B_OK;
}


/*static*/ VMAddressSpace*
VMAddressSpace::GetKernel()
{
	// we can treat this one a little differently since it can't be deleted
	sKernelAddressSpace->Get();
	return sKernelAddressSpace;
}


/*static*/ team_id
VMAddressSpace::CurrentID()
{
	struct thread* thread = thread_get_current_thread();

	if (thread != NULL && thread->team->address_space != NULL)
		return thread->team->id;

	return B_ERROR;
}


/*static*/ VMAddressSpace*
VMAddressSpace::GetCurrent()
{
	struct thread* thread = thread_get_current_thread();

	if (thread != NULL) {
		VMAddressSpace* addressSpace = thread->team->address_space;
		if (addressSpace != NULL) {
			addressSpace->Get();
			return addressSpace;
		}
	}

	return NULL;
}


/*static*/ VMAddressSpace*
VMAddressSpace::Get(team_id teamID)
{
	rw_lock_read_lock(&sAddressSpaceTableLock);
	VMAddressSpace* addressSpace = sAddressSpaceTable.Lookup(teamID);
	if (addressSpace)
		addressSpace->Get();
	rw_lock_read_unlock(&sAddressSpaceTableLock);

	return addressSpace;
}


//! You must hold the address space's read lock.
VMArea*
VMAddressSpace::LookupArea(addr_t address)
{
	// check the area hint first
	VMArea* area = fAreaHint;
	if (area != NULL && area->ContainsAddress(address))
		return area;

	for (area = areas; area != NULL; area = area->address_space_next) {
		if (area->id == RESERVED_AREA_ID)
			continue;

		if (area->ContainsAddress(address)) {
			fAreaHint = area;
			return area;
		}
	}

	return NULL;
}


//! You must hold the address space's write lock.
void
VMAddressSpace::RemoveArea(VMArea* area)
{
	VMArea* temp = areas;
	VMArea* last = NULL;

	while (temp != NULL) {
		if (area == temp) {
			if (last != NULL) {
				last->address_space_next = temp->address_space_next;
			} else {
				areas = temp->address_space_next;
			}
			IncrementChangeCount();
			break;
		}
		last = temp;
		temp = temp->address_space_next;
	}
	if (area == fAreaHint)
		fAreaHint = NULL;

	if (temp == NULL) {
		panic("VMAddressSpace::RemoveArea(): area not found in aspace's area "
			"list\n");
	}
}


void
VMAddressSpace::Dump() const
{
	kprintf("dump of address space at %p:\n", this);
	kprintf("id: 0x%lx\n", fID);
	kprintf("ref_count: %ld\n", fRefCount);
	kprintf("fault_count: %ld\n", fFaultCount);
	kprintf("translation_map: %p\n", &fTranslationMap);
	kprintf("base: 0x%lx\n", fBase);
	kprintf("size: 0x%lx\n", fSize);
	kprintf("change_count: 0x%lx\n", fChangeCount);
	kprintf("area_hint: %p\n", fAreaHint);

	kprintf("area_list:\n");

	VMArea* area;
	for (area = areas; area != NULL; area = area->address_space_next) {
		kprintf(" area 0x%lx: ", area->id);
		kprintf("base_addr = 0x%lx ", area->base);
		kprintf("size = 0x%lx ", area->size);
		kprintf("name = '%s' ", area->name);
		kprintf("protection = 0x%lx\n", area->protection);
	}
}


/*static*/ int
VMAddressSpace::_DumpCommand(int argc, char** argv)
{
	VMAddressSpace* aspace;

	if (argc < 2) {
		kprintf("aspace: not enough arguments\n");
		return 0;
	}

	// if the argument looks like a number, treat it as such

	{
		team_id id = strtoul(argv[1], NULL, 0);

		aspace = sAddressSpaceTable.Lookup(id);
		if (aspace == NULL) {
			kprintf("invalid aspace id\n");
		} else {
			aspace->Dump();
		}
		return 0;
	}
	return 0;
}


/*static*/ int
VMAddressSpace::_DumpListCommand(int argc, char** argv)
{
	kprintf("   address      id         base         size   area count   "
		" area size\n");

	AddressSpaceTable::Iterator it = sAddressSpaceTable.GetIterator();
	while (VMAddressSpace* space = it.Next()) {
		int32 areaCount = 0;
		off_t areaSize = 0;
		for (VMArea* area = space->areas; area != NULL;
				area = area->address_space_next) {
			if (area->id != RESERVED_AREA_ID
				&& area->cache->type != CACHE_TYPE_NULL) {
				areaCount++;
				areaSize += area->size;
			}
		}
		kprintf("%p  %6ld   %#010lx   %#10lx   %10ld   %10lld\n",
			space, space->ID(), space->Base(), space->Size(), areaCount,
			areaSize);
	}

	return 0;
}
