//----------------------------------------------------------------------
//  This software is part of the OpenBeOS distribution and is covered 
//  by the OpenBeOS license.
//---------------------------------------------------------------------
/*!
	\file intel.cpp
	\brief disk_scanner partition module for "intel" style partitions.
*/

// TODO: The implementation is very strict right now. It rejects a partition
// completely, if it finds an error in its partition tables. We should see,
// what error can be handled gracefully, e.g. by ignoring the partition
// descriptor or the whole partition table sector.

#include <errno.h>
#include <new>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <ddm_modules.h>
#include <DiskDeviceTypes.h>
#include <KernelExport.h>

#include "PartitionMap.h"

#define TRACE(x) ;
//#define TRACE(x) dprintf x

// module names
static const char *kPartitionMapModuleName
	= "partitioning_systems/intel/map/v1";
static const char *kExtendedPartitionModuleName
	= "partitioning_systems/intel/extended/v1";

// Maximal number of logical partitions per extended partition we allow.
static const int32 kMaxLogicalPartitionCount = 128;


// AutoDeleter

template<typename C>
class AutoDeleter {
public:
	AutoDeleter(C *object) : fObject(object)	{}
	~AutoDeleter()								{ delete fObject; }
	void SetObject(C *object)					{ fObject = object; }

private:
	C	*fObject;
};


// PartitionMapParser

class PartitionMapParser {
public:
	PartitionMapParser(int deviceFD, off_t sessionOffset, off_t sessionSize,
					   int32 blockSize);
	~PartitionMapParser();

	status_t Parse(const uint8 *block, PartitionMap *map);

	int32 CountPartitions() const;
	const Partition *PartitionAt(int32 index) const;

private:
	status_t _ParsePrimary(const partition_table_sector *pts);
	status_t _ParseExtended(PrimaryPartition *primary, off_t offset);
	status_t _ReadPTS(off_t offset, partition_table_sector *pts = NULL);

private:
	int						fDeviceFD;
	off_t					fSessionOffset;
	off_t					fSessionSize;
	int32					fBlockSize;
	partition_table_sector	*fPTS;	// while parsing
	PartitionMap			*fMap;	//
};

// constructor
PartitionMapParser::PartitionMapParser(int deviceFD, off_t sessionOffset,
									   off_t sessionSize, int32 blockSize)
	: fDeviceFD(deviceFD),
	  fSessionOffset(sessionOffset),
	  fSessionSize(sessionSize),
	  fBlockSize(blockSize),
	  fPTS(NULL),
	  fMap(NULL)
{
}

// destructor
PartitionMapParser::~PartitionMapParser()
{
}

// Parse
status_t
PartitionMapParser::Parse(const uint8 *block, PartitionMap *map)
{
	status_t error = (map ? B_OK : B_BAD_VALUE);
	if (error == B_OK) {
		fMap = map;
		fMap->Unset();
		if (block) {
			const partition_table_sector *pts
				= (const partition_table_sector*)block;
			error = _ParsePrimary(pts);
		} else {
			partition_table_sector pts;
			error = _ReadPTS(0, &pts);
			if (error == B_OK)
				error = _ParsePrimary(&pts);
		}
		if (error == B_OK && !fMap->Check(fSessionSize, fBlockSize))
			error = B_BAD_DATA;
		fMap = NULL;
	}
	return error;
}

// _ParsePrimary
status_t
PartitionMapParser::_ParsePrimary(const partition_table_sector *pts)
{
	status_t error = (pts ? B_OK : B_BAD_VALUE);
	// check the signature
	if (error == B_OK && pts->signature != kPartitionTableSectorSignature) {
		TRACE(("intel: _ParsePrimary(): invalid PTS signature\n"));
		error = B_BAD_DATA;
	}
	// examine the table
	if (error == B_OK) {
		for (int32 i = 0; i < 4; i++) {
			const partition_descriptor *descriptor = &pts->table[i];
			PrimaryPartition *partition = fMap->PrimaryPartitionAt(i);
			partition->SetTo(descriptor, 0, fBlockSize);
			// fail, if location is bad
			if (!partition->CheckLocation(fSessionSize, fBlockSize)) {
				error = B_BAD_DATA;
				break;
			}
		}
	}
	// allocate a PTS buffer
	if (error == B_OK) {
		fPTS = new(nothrow) partition_table_sector;
		if (!fPTS)
			error = B_NO_MEMORY;
	}
	// parse extended partitions
	if (error == B_OK) {
		for (int32 i = 0; error == B_OK && i < 4; i++) {
			PrimaryPartition *primary = fMap->PrimaryPartitionAt(i);
			if (primary->IsExtended())
				error = _ParseExtended(primary, primary->Offset());
		}
	}
	// cleanup
	if (fPTS) {
		delete fPTS;
		fPTS = NULL;
	}
	return error;
}

// _ParseExtended
status_t
PartitionMapParser::_ParseExtended(PrimaryPartition *primary, off_t offset)
{
	status_t error = B_OK;
	int32 partitionCount = 0;
	while (error == B_OK) {
		// check for cycles
		if (++partitionCount > kMaxLogicalPartitionCount) {
			TRACE(("intel: _ParseExtended(): Maximal number of logical "
				   "partitions for extended partition reached. Cycle?\n"));
			error = B_BAD_DATA;
		}
		// read the PTS
		if (error == B_OK)
			error = _ReadPTS(offset);
		// check the signature
		if (error == B_OK
			&& fPTS->signature != kPartitionTableSectorSignature) {
			TRACE(("intel: _ParseExtended(): invalid PTS signature\n"));
			error = B_BAD_DATA;
		}
		// ignore the PTS, if any error occured till now
		if (error != B_OK) {
			TRACE(("intel: _ParseExtended(): ignoring this PTS\n"));
			error = B_OK;
			break;
		}
		// examine the table
		LogicalPartition extended;
		LogicalPartition nonExtended;
		if (error == B_OK) {
			for (int32 i = 0; error == B_OK && i < 4; i++) {
				const partition_descriptor *descriptor = &fPTS->table[i];
				LogicalPartition *partition = NULL;
				if (!descriptor->is_empty()) {
					if (descriptor->is_extended()) {
						if (extended.IsEmpty()) {
							extended.SetTo(descriptor, offset, fBlockSize,
										   primary);
							partition = &extended;
						} else {
							// only one extended partition allowed
							error = B_BAD_DATA;
							TRACE(("intel: _ParseExtended(): "
								   "only one extended partition allowed\n"));
						}
					} else {
						if (nonExtended.IsEmpty()) {
							nonExtended.SetTo(descriptor, offset, fBlockSize,
											  primary);
							partition = &nonExtended;
						} else {
							// only one non-extended partition allowed
							error = B_BAD_DATA;
							TRACE(("intel: _ParseExtended(): only one "
								   "non-extended partition allowed\n"));
						}
					}
					// check the partition's location
					if (partition && !partition->CheckLocation(fSessionSize,
															   fBlockSize)) {
						error = B_BAD_DATA;
					}
				}
			}
		}
		// add non-extended partition to list
		if (error == B_OK && !nonExtended.IsEmpty()) {
			LogicalPartition *partition
				= new(nothrow) LogicalPartition(nonExtended);
			if (partition)
				primary->AddLogicalPartition(partition);
			else
				error = B_NO_MEMORY;
		}
		// prepare to parse next extended partition
		if (error == B_OK && !extended.IsEmpty())
			offset = extended.Offset();
		else
			break;
	}
	return error;
}

// _ReadPTS
status_t
PartitionMapParser::_ReadPTS(off_t offset, partition_table_sector *pts)
{
	status_t error = B_OK;
	if (!pts)
		pts = fPTS;
	int32 toRead = sizeof(partition_table_sector);
	// check the offset
	if (offset < 0 || offset + toRead > fSessionSize) {
		error = B_BAD_VALUE;
		TRACE(("intel: _ReadPTS(): bad offset: %Ld\n", offset));
	// read
	} else if (read_pos(fDeviceFD, fSessionOffset + offset, pts, toRead)
						!= toRead) {
		error = errno;
		if (error == B_OK)
			error = B_IO_ERROR;
		TRACE(("intel: _ReadPTS(): reading the PTS failed: %s\n",
			   strerror(error)));
	}
	return error;
}


// intel partition map module

// module
static status_t pm_std_ops(int32 op, ...);

// scanning
static float pm_identify_partition(int fd, partition_data *partition,
		void **cookie);
static status_t pm_scan_partition(int fd, partition_data *partition,
		void *cookie);
static void pm_free_identify_partition_cookie(partition_data *partition,
		void *cookie);
static void pm_free_partition_cookie(partition_data *partition);
static void pm_free_partition_content_cookie(partition_data *partition);

static partition_module_info intel_partition_map_module = {
	{
		kPartitionMapModuleName,
		0,
		pm_std_ops
	},
	kPartitionTypeIntel,				// pretty_name

	// scanning
	pm_identify_partition,				// identify_partition
	pm_scan_partition,					// scan_partition
	pm_free_identify_partition_cookie,	// free_identify_partition_cookie
	pm_free_partition_cookie,			// free_partition_cookie
	pm_free_partition_content_cookie,	// free_partition_content_cookie

	// querying
	NULL,								// supports_reparing_partition
	NULL,								// supports_resizing_partition
	NULL,								// supports_resizing_child_partition
	NULL,								// supports_moving_partition
	NULL,								// supports_moving_child_partition
	NULL,								// supports_creating_child_partition
	NULL,								// supports_parent_system
	NULL,								// supports_child_system
	NULL,								// validate_resize_partition
	NULL,								// validate_resize_child_partition
	NULL,								// validate_move_partition
	NULL,								// validate_move_child_partition
	NULL,								// validate_create_child_partition
	NULL,								// validate_initialize_partition
	NULL,								// validate_set_partition_parameters
	NULL,
								// validate_set_partition_content_parameters
	NULL,								// get_partitionable_spaces;

	// writing
	NULL,								// repair_partition
	NULL,								// resize_partition
	NULL,								// resize_child_partition
	NULL,								// move_partition
	NULL,								// move_child_partition
	NULL,								// create_child_partition
	NULL,								// delete_child_partition
	NULL,								// initialize_partition
	NULL,								// set_parameters_partition
	NULL,								// set_partition_content_parameters
};


// intel extended partition module

// module
static status_t ep_std_ops(int32 op, ...);

// scanning
static float ep_identify_partition(int fd, partition_data *partition,
		void **cookie);
static status_t ep_scan_partition(int fd, partition_data *partition,
		void *cookie);
static void ep_free_identify_partition_cookie(partition_data *partition,
		void *cookie);
static void ep_free_partition_cookie(partition_data *partition);
static void ep_free_partition_content_cookie(partition_data *partition);

static partition_module_info intel_extended_partition_module = {
	{
		kExtendedPartitionModuleName,
		0,
		ep_std_ops
	},
	kPartitionTypeIntelExtended,		// pretty_name

	// scanning
	ep_identify_partition,				// identify_partition
	ep_scan_partition,					// scan_partition
	ep_free_identify_partition_cookie,	// free_identify_partition_cookie
	ep_free_partition_cookie,			// free_partition_cookie
	ep_free_partition_content_cookie,	// free_partition_content_cookie

	// querying
	NULL,								// supports_reparing_partition
	NULL,								// supports_resizing_partition
	NULL,								// supports_resizing_child_partition
	NULL,								// supports_moving_partition
	NULL,								// supports_moving_child_partition
	NULL,								// supports_creating_child_partition
	NULL,								// supports_parent_system
	NULL,								// supports_child_system
	NULL,								// validate_resize_partition
	NULL,								// validate_resize_child_partition
	NULL,								// validate_move_partition
	NULL,								// validate_move_child_partition
	NULL,								// validate_create_child_partition
	NULL,								// validate_initialize_partition
	NULL,								// validate_set_partition_parameters
	NULL,
								// validate_set_partition_content_parameters
	NULL,								// get_partitionable_spaces;

	// writing
	NULL,								// repair_partition
	NULL,								// resize_partition
	NULL,								// resize_child_partition
	NULL,								// move_partition
	NULL,								// move_child_partition
	NULL,								// create_child_partition
	NULL,								// delete_child_partition
	NULL,								// initialize_partition
	NULL,								// set_parameters_partition
	NULL,								// set_partition_content_parameters
};


extern "C" partition_module_info *modules[];
_EXPORT partition_module_info *modules[] =
{
	&intel_partition_map_module,
	&intel_extended_partition_module,
	NULL
};


// intel partition map module

// pm_std_ops
static
status_t
pm_std_ops(int32 op, ...)
{
	TRACE(("intel: pm_std_ops(0x%lx)\n", op));
	switch(op) {
		case B_MODULE_INIT:
		case B_MODULE_UNINIT:
			return B_OK;
	}
	return B_ERROR;
}

// pm_identify_partition
static
float
pm_identify_partition(int fd, partition_data *partition, void **cookie)
{
	// check parameters
	if (fd < 0 || !partition || !cookie)
		return -1;
	TRACE(("intel: pm_identify_partition(%d, %ld: %lld, %lld, %ld)\n", fd,
		   partition->id, partition->offset, partition->size,
		   partition->block_size));
	// reject extended partitions
	if (partition->type
		&& !strcmp(partition->type, kPartitionTypeIntelExtended)) {
		return -1;
	}
	// check block size
	uint32 blockSize = partition->block_size;
	if (blockSize < sizeof(partition_table_sector)) {
		TRACE(("intel: read_partition_map: bad block size: %ld, should be "
			   ">= %ld\n", blockSize, sizeof(partition_table_sector)));
		return -1;
	}
	// allocate a PartitionMap
	PartitionMap *map = new(nothrow) PartitionMap;
	if (!map)
		return -1;
	// read the partition structure
	PartitionMapParser parser(fd, 0, partition->size, blockSize);
	status_t error = parser.Parse(NULL, map);
	if (error == B_OK) {
		*cookie = map;
		return 0.5;
	}
	// cleanup, if not detected
	delete map;
	return -1;
}

// pm_scan_partition
static
status_t
pm_scan_partition(int fd, partition_data *partition, void *cookie)
{
	AutoDeleter<PartitionMap> deleter((PartitionMap*)cookie);
	// check parameters
	if (fd < 0 || !partition || !cookie)
		return B_ERROR;
	TRACE(("intel: pm_scan_partition(%d, %ld: %lld, %lld, %ld)\n", fd,
		   partition->id, partition->offset, partition->size,
		   partition->block_size));
	PartitionMap *map = (PartitionMap*)cookie;
	// fill in the partition_data structure
	// (no content_name and content_parameters)
	partition->content_type = strdup(kPartitionTypeIntel);
	if (!partition->content_type)
		return B_NO_MEMORY;
	partition->content_cookie = map;
	// children
	status_t error = B_OK;
	int32 index = 0;
	for (int32 i = 0; i < 4; i++) {
		PrimaryPartition *primary = map->PrimaryPartitionAt(i);
		if (!primary->IsEmpty()) {
			partition_data *child = create_child_partition(partition->id,
														   index, -1);
			index++;
			if (!child) {
TRACE(("Creating child at index %ld failed\n", index - 1));
				// something went wrong
				error = B_ERROR;
				break;
			}
			child->offset = partition->offset + primary->Offset();
			child->size = primary->Size();
			child->block_size = partition->block_size;
			// (no name)
			char type[B_FILE_NAME_LENGTH];
			primary->GetTypeString(type);
			child->type = strdup(type);
			// parameters
			char buffer[128];
			sprintf(buffer, "type = %u ; active = %d", primary->Type(),
					primary->Active());
			child->parameters = strdup(buffer);
			child->cookie = primary;
			// check for allocation problems
			if (!child->type || !child->parameters) {
				error = B_NO_MEMORY;
				break;
			}
		}
	}
	// keep map on success or cleanup on error
	if (error == B_OK) {
		deleter.SetObject(NULL);
	} else {
		partition->content_cookie = NULL;
		for (int32 i = 0; i < partition->child_count; i++) {
			if (partition_data *child = get_child_partition(partition->id, i))
				child->cookie = NULL;
		}
	}
	return error;
}

// pm_free_identify_partition_cookie
static
void
pm_free_identify_partition_cookie(partition_data */*partition*/, void *cookie)
{
	if (cookie)
		delete (PartitionMap*)cookie;
}

// pm_free_partition_cookie
static
void
pm_free_partition_cookie(partition_data *partition)
{
	// called for the primary partitions: the PrimaryPartition is allocated
	// by the partition containing the partition map
	if (partition)
		partition->cookie = NULL;
}

// pm_free_partition_content_cookie
static
void
pm_free_partition_content_cookie(partition_data *partition)
{
	if (partition && partition->content_cookie) {
		delete (PartitionMap*)partition->content_cookie;
		partition->content_cookie = NULL;
	}
}


// intel extended partition module

// ep_std_ops
static
status_t
ep_std_ops(int32 op, ...)
{
	TRACE(("intel: ep_std_ops(0x%lx)\n", op));
	switch(op) {
		case B_MODULE_INIT:
		case B_MODULE_UNINIT:
			return B_OK;
	}
	return B_ERROR;
}

// ep_identify_partition
static
float
ep_identify_partition(int fd, partition_data *partition, void **cookie)
{
	// check parameters
	if (fd < 0 || !partition || !cookie || !partition->cookie)
		return -1;
	TRACE(("intel: ep_identify_partition(%d, %lld, %lld, %ld)\n", fd,
		   partition->offset, partition->size, partition->block_size));
	// our parent must be a intel partition map partition and we must have
	// extended partition type
	if (!partition->type
		|| strcmp(partition->type, kPartitionTypeIntelExtended)) {
		return -1;
	}
	partition_data *parent = get_parent_partition(partition->id);
	if (!parent || !parent->content_type
		|| strcmp(parent->content_type, kPartitionTypeIntel)) {
		return -1;
	}
	// things seem to be in order
	return 0.5;
}

// ep_scan_partition
static
status_t
ep_scan_partition(int fd, partition_data *partition, void *cookie)
{
	// check parameters
	if (fd < 0 || !partition || !partition->cookie)
		return B_ERROR;
	partition_data *parent = get_parent_partition(partition->id);
	if (!parent)
		return B_ERROR;
	PrimaryPartition *primary = (PrimaryPartition*)partition->cookie;
	// fill in the partition_data structure
	// (no content_name and content_parameters)
	partition->content_type = strdup(kPartitionTypeIntelExtended);
	if (!partition->content_type)
		return B_NO_MEMORY;
	partition->content_cookie = primary;
	// children
	status_t error = B_OK;
	int32 index = 0;
	for (int32 i = 0; i < primary->CountLogicalPartitions(); i++) {
		LogicalPartition *logical = primary->LogicalPartitionAt(i);
		partition_data *child = create_child_partition(partition->id,
													   index, -1);
		index++;
		if (!child) {
			// something went wrong
			error = B_ERROR;
			break;
		}
		child->offset = parent->offset + logical->Offset();
		child->size = logical->Size();
		child->block_size = partition->block_size;
		// (no name)
		char type[B_FILE_NAME_LENGTH];
		logical->GetTypeString(type);
		child->type = strdup(type);
		// parameters
		char buffer[128];
		sprintf(buffer, "type = %u ; active = %d", logical->Type(),
				logical->Active());
		child->parameters = strdup(buffer);
		child->cookie = logical;
		// check for allocation problems
		if (!child->type || !child->parameters) {
			error = B_NO_MEMORY;
			break;
		}
	}
	// cleanup on error
	if (error != B_OK) {
		partition->content_cookie = NULL;
		for (int32 i = 0; i < partition->child_count; i++) {
			if (partition_data *child = get_child_partition(partition->id, i))
				child->cookie = NULL;
		}
	}
	return error;
}

// ep_free_identify_partition_cookie
static
void
ep_free_identify_partition_cookie(partition_data *partition, void *cookie)
{
	// nothing to do
}

// ep_free_partition_cookie
static
void
ep_free_partition_cookie(partition_data *partition)
{
	// the logical partition's cookie belongs to the partition map partition
	if (partition)
		partition->cookie = NULL;
}

// ep_free_partition_content_cookie
static
void
ep_free_partition_content_cookie(partition_data *partition)
{
	// the extended partition's cookie belongs to the partition map partition
	if (partition)
		partition->content_cookie = NULL;
}

