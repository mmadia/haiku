/*
 * Copyright 2002-04, Thomas Kurschel. All rights reserved.
 * Distributed under the terms of the MIT License.
 */

/*
	Generic IDE adapter library.

	The correct name would be ATA adapter, but I chose the old name as it's
	more widely known.
*/

#include <KernelExport.h>
#include <malloc.h>
#include <string.h>

#include <device_manager.h>
#include <bus/PCI.h>
#include <bus/IDE.h>
#include <ide_types.h>
#include <ide_adapter.h>
#include <block_io.h>
#include <lendian_bitfield.h>

#define debug_level_flow 0
#define debug_level_error 3
#define debug_level_info 3

#define DEBUG_MSG_PREFIX "IDE PCI -- "

#include "wrapper.h"

#define TRACE dprintf


static ide_for_controller_interface *ide;
static device_manager_info *pnp;


static status_t
ide_adapter_write_command_block_regs(ide_adapter_channel_info *channel,
	ide_task_file *tf, ide_reg_mask mask)
{
	pci_device_module_info *pci = channel->pci;
	pci_device device = channel->device;
	int i;

	uint16 ioaddr = channel->command_block_base;

	if (channel->lost)
		return B_ERROR;

	for (i = 0; i < 7; i++) {
		if (((1 << (i-7)) & mask) != 0) {
			SHOW_FLOW( 4, "%x->HI(%x)", tf->raw.r[i + 7], i );
			pci->write_io_8(device, ioaddr + 1 + i, tf->raw.r[i + 7]);
		}

		if (((1 << i) & mask) != 0) {
			SHOW_FLOW( 4, "%x->LO(%x)", tf->raw.r[i], i );
			pci->write_io_8(device, ioaddr + 1 + i, tf->raw.r[i]);
		}
	}

	return B_OK;
}


static status_t
ide_adapter_read_command_block_regs(ide_adapter_channel_info *channel,
	ide_task_file *tf, ide_reg_mask mask)
{
	pci_device_module_info *pci = channel->pci;
	pci_device device = channel->device;
	int i;

	uint16 ioaddr = channel->command_block_base;

	if (channel->lost)
		return B_ERROR;

	for (i = 0; i < 7; i++) {
		if (((1 << i) & mask) != 0) {
			tf->raw.r[i] = pci->read_io_8(device, ioaddr + 1 + i);
			SHOW_FLOW( 4, "%x: %x", i, (int)tf->raw.r[i] );
		}
	}

	return B_OK;
}


static uint8
ide_adapter_get_altstatus(ide_adapter_channel_info *channel)
{
	pci_device_module_info *pci = channel->pci;
	pci_device device = channel->device;
	uint16 altstatusaddr = channel->control_block_base;

	if (channel->lost)
		return 0x01; // Error bit

	return pci->read_io_8(device, altstatusaddr);
}


static status_t
ide_adapter_write_device_control(ide_adapter_channel_info *channel, uint8 val)
{
	pci_device_module_info *pci = channel->pci;
	pci_device device = channel->device;
	uint16 device_control_addr = channel->control_block_base;

	SHOW_FLOW(3, "%x", (int)val);

	if (channel->lost)
		return B_ERROR;

	pci->write_io_8(device, device_control_addr, val);

	return B_OK;
}


static status_t
ide_adapter_write_pio(ide_adapter_channel_info *channel, uint16 *data,
	int count, bool force_16bit)
{
	pci_device_module_info *pci = channel->pci;
	pci_device device = channel->device;

	uint16 ioaddr = channel->command_block_base;

	if (channel->lost)
		return B_ERROR;

	if ((count & 1) != 0 || force_16bit) {
		for (; count > 0; --count)
			pci->write_io_16(device, ioaddr, *(data++));
	} else {
		uint32 *cur_data = (uint32 *)data;

		for (; count > 0; count -= 2)
			pci->write_io_32(device, ioaddr, *(cur_data++));
	}

	return B_OK;
}


static status_t
ide_adapter_read_pio(ide_adapter_channel_info *channel, uint16 *data,
	int count, bool force_16bit)
{
	pci_device_module_info *pci = channel->pci;
	pci_device device = channel->device;

	uint16 ioaddr = channel->command_block_base;

	if (channel->lost)
		return B_ERROR;

	force_16bit = true;

	if ((count & 1) != 0 || force_16bit) {
		for (; count > 0; --count)
			*(data++) = pci->read_io_16(device, ioaddr );
	} else {
		uint32 *cur_data = (uint32 *)data;

		for (; count > 0; count -= 2)
			*(cur_data++) = pci->read_io_32(device, ioaddr);
	}

	return B_OK;
}


static int32
ide_adapter_inthand(void *arg)
{
	ide_adapter_channel_info *channel = (ide_adapter_channel_info *)arg;
	pci_device_module_info *pci = channel->pci;
	pci_device device = channel->device;
	uint8 status;

	SHOW_FLOW0(3, "");

	if (channel->lost)
		return B_UNHANDLED_INTERRUPT;

	// add test whether this is really our IRQ
	if (channel->dmaing) {
		// in DMA mode, there is a safe test
		// in PIO mode, this don't work
		status = pci->read_io_8(device, channel->bus_master_base
			+ IDE_BM_STATUS_REG);
		if ((status & IDE_BM_STATUS_INTERRUPT) == 0)
			return B_UNHANDLED_INTERRUPT;
	}

	// acknowledge IRQ
	status = pci->read_io_8(device, channel->command_block_base + 7);

	return ide->irq_handler(channel->ide_channel, status);
}


static status_t
ide_adapter_prepare_dma(ide_adapter_channel_info *channel,
	const physical_entry *sgList, size_t sgListCount, bool writeToDevice)
{
	pci_device_module_info *pci = channel->pci;
	pci_device device = channel->device;
	uint8 command;
	uint8 status;
	prd_entry *prd = channel->prdt;
	int i;

	for (i = sgListCount - 1, prd = channel->prdt; i >= 0; --i, ++prd, ++sgList) {
		prd->address = B_HOST_TO_LENDIAN_INT32(pci->ram_address(device, sgList->address));
		// 0 means 64K - this is done automatically be discarding upper 16 bits
		prd->count = B_HOST_TO_LENDIAN_INT16((uint16)sgList->size);
		prd->EOT = i == 0;

		SHOW_FLOW( 4, "%x, %x, %d", (int)prd->address, prd->count, prd->EOT);
	}

	pci->write_io_32(device, channel->bus_master_base + IDE_BM_PRDT_ADDRESS, 
		(pci->read_io_32(device, channel->bus_master_base + IDE_BM_PRDT_ADDRESS) & 3)
		| (B_HOST_TO_LENDIAN_INT32(pci->ram_address(device, (void *)channel->prdt_phys)) & ~3));

	// reset interrupt and error signal
	status = pci->read_io_8(device, channel->bus_master_base
		+ IDE_BM_STATUS_REG) | IDE_BM_STATUS_INTERRUPT | IDE_BM_STATUS_ERROR;
	pci->write_io_8(device, 
		channel->bus_master_base + IDE_BM_STATUS_REG, status);

	// set data direction
	command = pci->read_io_8(device, channel->bus_master_base
		+ IDE_BM_COMMAND_REG);
	if (writeToDevice)
		command &= ~IDE_BM_COMMAND_READ_FROM_DEVICE;
	else
		command |= IDE_BM_COMMAND_READ_FROM_DEVICE;

	pci->write_io_8(device, channel->bus_master_base + IDE_BM_COMMAND_REG,
		command);

	return B_OK;
}


static status_t
ide_adapter_start_dma(ide_adapter_channel_info *channel)
{
	pci_device_module_info *pci = channel->pci;
	pci_device device = channel->device;
	uint8 command;

	command = pci->read_io_8(device, channel->bus_master_base
		+ IDE_BM_COMMAND_REG);

	command |= IDE_BM_COMMAND_START_STOP;
	channel->dmaing = true;

	pci->write_io_8(device, channel->bus_master_base + IDE_BM_COMMAND_REG,
		command);

	return B_OK;
}


static status_t
ide_adapter_finish_dma(ide_adapter_channel_info *channel)
{
	pci_device_module_info *pci = channel->pci;
	pci_device device = channel->device;
	uint8 command;
	uint8 status, newStatus;

	command = pci->read_io_8(device, channel->bus_master_base
		+ IDE_BM_COMMAND_REG);

	command &= ~IDE_BM_COMMAND_START_STOP;
	channel->dmaing = false;

	pci->write_io_8(device, channel->bus_master_base + IDE_BM_COMMAND_REG,
		command);

	status = pci->read_io_8(device, channel->bus_master_base
		+ IDE_BM_STATUS_REG);

	// reset interrupt/error flags
	newStatus = status | IDE_BM_STATUS_INTERRUPT | IDE_BM_STATUS_ERROR;
	pci->write_io_8(device, channel->bus_master_base + IDE_BM_STATUS_REG,
		newStatus);

	if ((status & IDE_BM_STATUS_ERROR) != 0)
		return B_ERROR;

	if ((status & IDE_BM_STATUS_INTERRUPT) == 0) {
		if ((status & IDE_BM_STATUS_ACTIVE) != 0) {
			SHOW_ERROR0( 2, "DMA transfer aborted" );
			return B_ERROR;
		}

		SHOW_ERROR0( 2, "DMA transfer: buffer underrun" );
		return B_DEV_DATA_UNDERRUN;
	}

	if ((status & IDE_BM_STATUS_ACTIVE) != 0) {
		SHOW_ERROR0( 2, "DMA transfer: buffer too large" );
		return B_DEV_DATA_OVERRUN;
	}

	return B_OK;
}


static status_t
ide_adapter_init_channel(device_node_handle node, ide_channel ide_channel,
	ide_adapter_channel_info **cookie, size_t total_data_size,
	int32 (*inthand)(void *arg))
{
	ide_adapter_controller_info *controller;
	ide_adapter_channel_info *channel;
	uint16 command_block_base, control_block_base;
	uint8 intnum;
	int prdt_size;
	physical_entry pe[1];
	uint8 is_primary;
	status_t res;

	TRACE("PCI-IDE: init channel...\n");

	// get device data
	if (pnp->get_attr_uint16(node, IDE_ADAPTER_COMMAND_BLOCK_BASE, &command_block_base, false) != B_OK
		|| pnp->get_attr_uint16(node, IDE_ADAPTER_CONTROL_BLOCK_BASE, &control_block_base, false) != B_OK
		|| pnp->get_attr_uint8(node, IDE_ADAPTER_INTNUM, &intnum, true) != B_OK
		|| pnp->get_attr_uint8(node, IDE_ADAPTER_IS_PRIMARY, &is_primary, false) != B_OK)
		return B_ERROR;

	if (pnp->init_driver(pnp->get_parent(node), NULL, NULL, (void **)&controller) != B_OK)
		return B_ERROR;

	channel = (ide_adapter_channel_info *)malloc(total_data_size);
	if (channel == NULL) {
		res = B_NO_MEMORY;
		goto err;
	}

	channel->node = node;
	channel->pci = controller->pci;
	channel->device = controller->device;
	channel->lost = false;
	channel->command_block_base = command_block_base;
	channel->control_block_base = control_block_base;
	channel->bus_master_base = controller->bus_master_base + (is_primary ? 0 : 8);
	channel->intnum = intnum;
	channel->ide_channel = ide_channel;
	channel->dmaing = false;
	channel->inthand = inthand;

	// PRDT must be contiguous, dword-aligned and must not cross 64K boundary 
	prdt_size = (IDE_ADAPTER_MAX_SG_COUNT * sizeof( prd_entry ) + (B_PAGE_SIZE - 1)) & ~(B_PAGE_SIZE - 1);
	channel->prd_area = create_area("prd", (void **)&channel->prdt, B_ANY_KERNEL_ADDRESS, 
		prdt_size, B_FULL_LOCK | B_CONTIGUOUS, 0);
	if (channel->prd_area < B_OK) {
		res = channel->prd_area;
		goto err2;
	}

	get_memory_map(channel->prdt, prdt_size, pe, 1);
	channel->prdt_phys = (uint32)pe[0].address;

	SHOW_FLOW(3, "virt=%p, phys=%x", channel->prdt, (int)channel->prdt_phys);

	res = install_io_interrupt_handler(channel->intnum, 
		inthand, channel, 0);

	if (res < 0) {
		SHOW_ERROR(0, "couldn't install irq handler @%d", channel->intnum);
		goto err3;
	}

	TRACE("PCI-IDE: init channel done\n");
	// enable interrupts so the channel is ready to run
	ide_adapter_write_device_control(channel, ide_devctrl_bit3);
	
	*cookie = channel;
	
	return B_OK;

err3:
	delete_area(channel->prd_area);
err2:
	pnp->uninit_driver(pnp->get_parent(node));
err:
	free(channel);

	return res;
}


static status_t
ide_adapter_uninit_channel(ide_adapter_channel_info *channel)
{
	// disable IRQs
	ide_adapter_write_device_control(channel, ide_devctrl_bit3 | ide_devctrl_nien);

	// catch spurious interrupt
	// (some controllers generate an IRQ when you _disable_ interrupts,
	//  they are delayed by less then 40 µs, so 1 ms is safe)
	snooze(1000);

	remove_io_interrupt_handler(channel->intnum, channel->inthand, channel);

	pnp->uninit_driver( pnp->get_parent(channel->node));

	delete_area(channel->prd_area);
	free(channel);

	return B_OK;
}


static void
ide_adapter_channel_removed(device_node_handle node, ide_adapter_channel_info *channel)
{
	SHOW_FLOW0( 3, "" );

	if (channel != NULL)
		// disable access instantly
		atomic_or(&channel->lost, 1);
}


/** publish node of ide channel */

static status_t
ide_adapter_publish_channel(device_node_handle controller_node, 
	const char *channel_module_name, uint16 command_block_base,
	uint16 control_block_base, uint8 intnum, bool can_dma,
	bool is_primary, const char *name, io_resource_handle *resources,
	device_node_handle *node)
{
	device_attr attrs[] = {
		// info about ourself and our consumer
		{ B_DRIVER_MODULE, B_STRING_TYPE, { string: channel_module_name }},
		{ B_DRIVER_PRETTY_NAME, B_STRING_TYPE, { string: "IDE PCI" }},
		{ PNP_DRIVER_CONNECTION, B_STRING_TYPE, { string: name }},
		{ B_DRIVER_FIXED_CHILD, B_STRING_TYPE, { string: IDE_FOR_CONTROLLER_MODULE_NAME }},

		// private data to identify channel
		{ IDE_ADAPTER_COMMAND_BLOCK_BASE, B_UINT16_TYPE, { ui16: command_block_base }},
		{ IDE_ADAPTER_CONTROL_BLOCK_BASE, B_UINT16_TYPE, { ui16: control_block_base }},
		{ IDE_CONTROLLER_CAN_DMA_ITEM, B_UINT8_TYPE, { ui8: can_dma }},
		{ IDE_ADAPTER_INTNUM, B_UINT8_TYPE, { ui8: intnum }},
		{ IDE_ADAPTER_IS_PRIMARY, B_UINT8_TYPE, { ui8: is_primary }},
		{ NULL }
	};

	SHOW_FLOW0(2, "");

	return pnp->register_device(controller_node, attrs, resources, node);
}


/** detect IDE channel */

static status_t
ide_adapter_detect_channel(pci_device_module_info *pci, pci_device pci_device,
	device_node_handle controller_node, const char *channel_module_name,
	bool controller_can_dma, uint16 command_block_base, uint16 control_block_base,
	uint16 bus_master_base, uint8 intnum, bool is_primary, const char *name,
	device_node_handle *node, bool supports_compatibility_mode)
{
	uint8 api;
	io_resource_handle resource_handles[3];

	SHOW_FLOW0( 3, "" );

	// if channel works in compatibility mode, addresses and interrupt are fixed
	api = pci->read_pci_config(pci_device, PCI_class_api, 1);

	if (supports_compatibility_mode
		&& is_primary && (api & IDE_API_PRIMARY_NATIVE) == 0) {
		command_block_base = 0x1f0;
		control_block_base = 0x3f6;
		intnum = 14;
		TRACE("PCI-IDE: Controller in legacy mode: cmd %#x, ctrl %#x, irq %d\n",
			  command_block_base, control_block_base, intnum);
	} else if (supports_compatibility_mode
		&& !is_primary && (api & IDE_API_PRIMARY_NATIVE) == 0) {
		command_block_base = 0x170;
		control_block_base = 0x376;
		intnum = 15;
		TRACE("PCI-IDE: Controller in legacy mode: cmd %#x, ctrl %#x, irq %d\n",
			  command_block_base, control_block_base, intnum);
	} else {
		if (command_block_base == 0 || control_block_base == 0) {
			TRACE("PCI-IDE: Command/Control Block base is not configured\n");
			return B_ERROR;
		}
		if (intnum == 0 || intnum == 0xff) {
			TRACE("PCI-IDE: Interrupt is not configured\n");
			return B_ERROR;
		}

		// historically, they start at 3f6h/376h, but PCI spec requires registers
		// to be aligned at 4 bytes, so only 3f4h/374h can be specified; thus
		// PCI IDE defines that control block starts at offset 2
		control_block_base += 2;
		TRACE("PCI-IDE: Controller in native mode: cmd %#x, ctrl %#x, irq %d\n",
			  command_block_base, control_block_base, intnum);
	}

	if (supports_compatibility_mode) {
		// read status of primary(!) channel to detect simplex
		uint8 status = pci->read_io_8(pci_device, bus_master_base
			+ IDE_BM_STATUS_REG);

		if (status & IDE_BM_STATUS_SIMPLEX_DMA && !is_primary) {
			// in simplex mode, channels cannot operate independantly of each other;
			// we simply disable bus mastering of second channel to satisfy that;
			// better were to use a controller lock, but this had to be done in the IDE
			// bus manager, and I don't see any reason to add extra code for old
			// simplex controllers
			TRACE("PCI-IDE: Simplex controller - disabling DMA of secondary channel\n");
			controller_can_dma = false;
		}
	}

	bus_master_base += is_primary ? 0 : 8;

	TRACE("PCI-IDE: bus master base %#x\n", bus_master_base);

	{
		// allocate channel's I/O resources
		io_resource resources[3] = {
			{ IO_PORT, command_block_base, 8 },
			{ IO_PORT, control_block_base, 1 },
			{}
		};

		if (pnp->acquire_io_resources(resources, resource_handles) != B_OK) {
			TRACE("PCI-IDE: Couldn't acquire channel resources %#x and %#x\n",
				  command_block_base, control_block_base);
			return B_ERROR;
		}
	}

	return ide_adapter_publish_channel(controller_node, channel_module_name,
		command_block_base, control_block_base, intnum, controller_can_dma,
		is_primary, name, resource_handles, node);
}


static status_t
ide_adapter_init_controller(device_node_handle node, void *user_cookie,
	ide_adapter_controller_info **cookie, size_t total_data_size)
{
	pci_device_module_info *pci;
	pci_device device;
	ide_adapter_controller_info *controller;
	uint16 bus_master_base;

	// get device data	
	if (pnp->get_attr_uint16(node, IDE_ADAPTER_BUS_MASTER_BASE, &bus_master_base, false) != B_OK)
		return B_ERROR;

	if (pnp->init_driver(pnp->get_parent(node), NULL, (driver_module_info **)&pci, (void **)&device) != B_OK)
		return B_ERROR;

	controller = (ide_adapter_controller_info *)malloc(total_data_size);
	if (controller == NULL)
		return B_NO_MEMORY;

	controller->node = node;
	controller->pci = pci;
	controller->device = device;
	controller->lost = false;
	controller->bus_master_base = bus_master_base;
	
	*cookie = controller;
	
	return B_OK;
}


static status_t
ide_adapter_uninit_controller(ide_adapter_controller_info *controller)
{
	pnp->uninit_driver(pnp->get_parent(controller->node));

	free(controller);

	return B_OK;
}


static void
ide_adapter_controller_removed(device_node_handle node,
	ide_adapter_controller_info *controller)
{
	SHOW_FLOW0(3, "");

	if (controller != NULL)
		// disable access instantly; unit_device takes care of unregistering ioports
		atomic_or(&controller->lost, 1);
}


/** publish node of ide controller */

static status_t
ide_adapter_publish_controller(device_node_handle parent, uint16 bus_master_base,
	io_resource_handle *resources, const char *controller_driver,
	const char *controller_driver_type, const char *controller_name, bool can_dma,
	bool can_cq, uint32 dma_alignment, uint32 dma_boundary, uint32 max_sg_block_size,
	device_node_handle *node)
{
	device_attr attrs[] = {
		// info about ourself and our consumer
		{ B_DRIVER_MODULE, B_STRING_TYPE, { string: controller_driver }},

		// properties of this controller for ide bus manager
		// there are always max. 2 devices 
		// (unless this is a Compact Flash Card with a built-in IDE controller,
		//  which has exactly 1 device)
		{ IDE_CONTROLLER_MAX_DEVICES_ITEM, B_UINT8_TYPE, { ui8: 2 }},
		// of course we can DMA
		{ IDE_CONTROLLER_CAN_DMA_ITEM, B_UINT8_TYPE, { ui8: can_dma }},
		// command queuing always works (unless controller is buggy)
		{ IDE_CONTROLLER_CAN_CQ_ITEM, B_UINT8_TYPE, { ui8: can_cq }},
		// choose any name here
		{ IDE_CONTROLLER_CONTROLLER_NAME_ITEM, B_STRING_TYPE, { string: controller_name }},

		// DMA properties
		// data must be word-aligned; 
		// warning: some controllers are more picky!
		{ B_BLOCK_DEVICE_DMA_ALIGNMENT, B_UINT32_TYPE, { ui32: dma_alignment /*1*/}},
		// one S/G block must not cross 64K boundary
		{ B_BLOCK_DEVICE_DMA_BOUNDARY, B_UINT32_TYPE, { ui32: dma_boundary/*0xffff*/ }},
		// max size of S/G block is 16 bits with zero being 64K
		{ B_BLOCK_DEVICE_MAX_SG_BLOCK_SIZE, B_UINT32_TYPE, { ui32: max_sg_block_size/*0x10000*/ }},
		// see definition of MAX_SG_COUNT
		{ B_BLOCK_DEVICE_MAX_SG_BLOCKS, B_UINT32_TYPE, { ui32: IDE_ADAPTER_MAX_SG_COUNT }},

		// private data to find controller
		{ IDE_ADAPTER_BUS_MASTER_BASE, B_UINT16_TYPE, { ui16: bus_master_base }},
		{ NULL }
	};

	SHOW_FLOW0( 2, "" );

	return pnp->register_device(parent, attrs, resources, node);
}


/** detect pure IDE controller, i.e. without channels */

static status_t
ide_adapter_detect_controller(pci_device_module_info *pci, pci_device pci_device,
	device_node_handle parent,	uint16 bus_master_base,	const char *controller_driver,
	const char *controller_driver_type, const char *controller_name, bool can_dma,
	bool can_cq, uint32 dma_alignment, uint32 dma_boundary, uint32 max_sg_block_size,
	device_node_handle *node)
{
	io_resource_handle resource_handles[2];

	SHOW_FLOW0( 3, "" );

	if (bus_master_base == 0) {
		TRACE("PCI-IDE: Controller detection failed! bus master base not configured\n");
		return B_ERROR;
	}

	{
		io_resource resources[2] = {
			{ IO_PORT, bus_master_base, 16 },
			{}
		};

		if (pnp->acquire_io_resources(resources, resource_handles) != B_OK) {
			TRACE("PCI-IDE: Couldn't acquire controller resource %#x\n", bus_master_base);
			return B_ERROR;
		}
	}

	return ide_adapter_publish_controller(parent, bus_master_base, resource_handles,
		controller_driver, controller_driver_type, controller_name, can_dma, can_cq,
		dma_alignment, dma_boundary, max_sg_block_size, node);
}


static status_t
ide_adapter_probe_controller(device_node_handle parent, const char *controller_driver,
	const char *controller_driver_type, const char *controller_name,
	const char *channel_module_name, bool can_dma, bool can_cq, uint32 dma_alignment,
	uint32 dma_boundary, uint32 max_sg_block_size, bool supports_compatibility_mode)
{
	pci_device_module_info *pci;
	pci_device device;
	uint16 command_block_base[2];
	uint16 control_block_base[2];
	uint16 bus_master_base;
	device_node_handle controller_node, channels[2];
	uint8 intnum;
	status_t res;

	SHOW_FLOW0( 3, "" );

	if (pnp->init_driver(parent, NULL, (driver_module_info **)&pci, (void **)&device) != B_OK)
		return B_ERROR;

	command_block_base[0] = pci->read_pci_config(device, PCI_base_registers, 4 );
	control_block_base[0] = pci->read_pci_config(device, PCI_base_registers + 4, 4);
	command_block_base[1] = pci->read_pci_config(device, PCI_base_registers + 8, 4);
	control_block_base[1] = pci->read_pci_config(device, PCI_base_registers + 12, 4);
	bus_master_base = pci->read_pci_config(device, PCI_base_registers + 16, 4);
	intnum = pci->read_pci_config(device, PCI_interrupt_line, 1);

	command_block_base[0] &= ~PCI_address_space;
	control_block_base[0] &= ~PCI_address_space;
	command_block_base[1] &= ~PCI_address_space;
	control_block_base[1] &= ~PCI_address_space;
	bus_master_base &= ~PCI_address_space;

	res = ide_adapter_detect_controller(pci, device, parent, bus_master_base, 
		controller_driver, controller_driver_type, controller_name, can_dma,
		can_cq, dma_alignment, dma_boundary, max_sg_block_size, &controller_node);
	// don't register if controller is already registered!
	// (happens during rescan; registering new channels would kick out old channels)
	if (res != B_OK || controller_node == NULL)
		goto err;

	// ignore errors during registration of channels - could be a simple rescan collision
	ide_adapter_detect_channel(pci, device, controller_node, channel_module_name,
		can_dma, command_block_base[0], control_block_base[0], bus_master_base,
		intnum, true, "Primary Channel", &channels[0], supports_compatibility_mode);

	ide_adapter_detect_channel(pci, device, controller_node, channel_module_name,
		can_dma, command_block_base[1], control_block_base[1], bus_master_base,
		intnum, false, "Secondary Channel", &channels[1], supports_compatibility_mode);
	
	pnp->uninit_driver(parent);
		
	return B_OK;
	
err:
	pnp->uninit_driver(parent);	
	return res;
}


static status_t
std_ops(int32 op, ...)
{
	switch (op) {
		case B_MODULE_INIT:
		case B_MODULE_UNINIT:
			return B_OK;

		default:
			return B_ERROR;
	}
}


module_dependency module_dependencies[] = {
	{ IDE_FOR_CONTROLLER_MODULE_NAME, (module_info **)&ide },
	{ B_DEVICE_MANAGER_MODULE_NAME, (module_info **)&pnp },
	{}
};


static ide_adapter_interface adapter_interface = {
	{
		IDE_ADAPTER_MODULE_NAME,
		0,
		std_ops
	},

	ide_adapter_write_command_block_regs,
	ide_adapter_read_command_block_regs,
	 
	ide_adapter_get_altstatus,
	ide_adapter_write_device_control,
	
	ide_adapter_write_pio,
	ide_adapter_read_pio,
	
	ide_adapter_prepare_dma,
	ide_adapter_start_dma,
	ide_adapter_finish_dma,

	ide_adapter_inthand,
	
	ide_adapter_init_channel,
	ide_adapter_uninit_channel,
	ide_adapter_channel_removed,

	ide_adapter_publish_channel,
	ide_adapter_detect_channel,

	ide_adapter_init_controller,
	ide_adapter_uninit_controller,
	ide_adapter_controller_removed,

	ide_adapter_publish_controller,
	ide_adapter_detect_controller,

	ide_adapter_probe_controller
};

module_info *modules[] = {
	&adapter_interface.info,
	NULL
};
