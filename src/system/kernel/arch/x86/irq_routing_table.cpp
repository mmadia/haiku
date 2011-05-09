/*
 * Copyright 2011, Michael Lotz mmlr@mlotz.ch.
 * Copyright 2009, Clemens Zeidler haiku@clemens-zeidler.de.
 * All rights reserved.
 *
 * Distributed under the terms of the MIT License.
 */


#include "irq_routing_table.h"

#include "acpi.h"

#include <int.h>

#include <PCI.h>


//#define TRACE_PRT
#ifdef TRACE_PRT
#	define TRACE(x...) dprintf("IRQRoutingTable: "x)
#else
#	define TRACE(x...)
#endif


const char* kACPIPciRootName = "PNP0A03";
const char* kACPIPciExpressRootName = "PNP0A08";
	// Note that some configurations will still return the PCI express root
	// when querying for the standard PCI root. This is due to the compatible ID
	// fields in ACPI. TODO: Query both/the correct root device.


irq_descriptor::irq_descriptor()
	:
	irq(0),
	shareable(false),
	polarity(B_HIGH_ACTIVE_POLARITY),
	trigger_mode(B_EDGE_TRIGGERED)
{
}


void
print_irq_descriptor(irq_descriptor* descriptor)
{
	const char* activeHighString = "active high";
	const char* activeLowString = " active low";
	const char* levelTriggeredString = "level triggered";
	const char* edgeTriggeredString = "edge triggered";

	dprintf("irq: %u, shareable: %u, polarity: %s, trigger_mode: %s\n",
		descriptor->irq, descriptor->shareable,
		descriptor->polarity == B_HIGH_ACTIVE_POLARITY ? activeHighString
			: activeLowString,
		descriptor->trigger_mode == B_LEVEL_TRIGGERED ? levelTriggeredString
			: edgeTriggeredString);
}


static void
print_irq_routing_entry(const irq_routing_entry& entry)
{
	dprintf("address 0x%04llx; pin %u;", entry.device_address, entry.pin);

	if (entry.source_index != 0)
		dprintf(" GSI %lu;", entry.source_index);
	else
		dprintf(" source %p %lu;", entry.source, entry.source_index);

	dprintf(" pci %u:%u pin %u; gsi %u; config 0x%02x\n", entry.pci_bus,
		entry.pci_device, entry.pin + 1, entry.irq,
		entry.polarity | entry.trigger_mode);
}


void
print_irq_routing_table(IRQRoutingTable* table)
{
	dprintf("IRQ routing table with %i entries\n", (int)table->Count());
	for (int i = 0; i < table->Count(); i++)
		print_irq_routing_entry(table->ElementAt(i));
}


static status_t
update_pci_info_for_entry(pci_module_info* pci, irq_routing_entry& entry)
{
	// check the base device at function 0
	uint8 headerType = pci->read_pci_config(entry.pci_bus, entry.pci_device, 0,
		PCI_header_type, 1);
	switch (headerType & PCI_header_type_mask) {
		case PCI_header_type_generic:
		case PCI_header_type_PCI_to_PCI_bridge:
			// We don't really care about bridges as we won't install
			// interrupt handlers for them, but we can still map them and
			// update their info for completeness.
			break;

		default:
			// either an unsupported or a non-present device (0xff)
			return B_ENTRY_NOT_FOUND;
	}

	// we have a device, check how many functions we need to iterate
	uint8 functionCount = 1;
	if ((headerType & PCI_multifunction) != 0) {
		functionCount = 8;
			// TODO: as per PCI 3.0, the PCI module hardcodes it in various
			// places as well...
	}

	uint32 updateCount = 0;
	for (uint8 function = 0; function < functionCount; function++) {
		// check for device presence by looking for a valid vendor
		uint16 vendorId = pci->read_pci_config(entry.pci_bus, entry.pci_device,
			function, PCI_vendor_id, 2);
		if (vendorId == 0xffff)
			continue;

		uint8 interruptPin = pci->read_pci_config(entry.pci_bus,
			entry.pci_device, function, PCI_interrupt_pin, 1);

		// Finally match the pin with the entry, note that PCI pins are 1 based
		// while ACPI ones are 0 based.
		if (interruptPin == entry.pin + 1) {
			if (pci->update_interrupt_line(entry.pci_bus, entry.pci_device,
				function, entry.irq) == B_OK) {
				updateCount++;
			}
		}
	}

	return updateCount > 0 ? B_OK : B_ENTRY_NOT_FOUND;
}


static status_t
configure_link_device(acpi_module_info* acpi, acpi_handle handle,
	irq_descriptor& result)
{
	status_t status = read_possible_irq(acpi, handle, &result);
	if (status != B_OK) {
		dprintf("failed to read possible IRQ configuration of link device\n");

		// We could try returning the current config as a fallback, but it most
		// probably is invalid as it points to the legacy config the BIOS has
		// done in PIC mode.
		return status;
	}

	// TODO: Blindly set the first possible configuration (obviously not what we
	// want to do as it will most probably result in a "everything to single
	// IRQ" config; anyway just to get things going...)
	return set_current_irq(acpi, handle, &result);
}


static status_t
evaluate_integer(acpi_module_info* acpi, acpi_handle handle,
	const char* method, uint64& value)
{
	acpi_object_type result;
	acpi_data resultBuffer;
	resultBuffer.pointer = &result;
	resultBuffer.length = sizeof(result);

	status_t status = acpi->evaluate_method(handle, method, NULL,
		&resultBuffer);
	if (status != B_OK)
		return status;

	if (result.object_type != ACPI_TYPE_INTEGER)
		return B_BAD_TYPE;

	value = result.data.integer;
	return B_OK;
}


static void
read_irq_routing_table_recursive(acpi_module_info* acpi, pci_module_info* pci,
	acpi_handle device, const pci_address& parentAddress,
	IRQRoutingTable* table, bool rootBridge)
{
	acpi_data buffer;
	buffer.pointer = NULL;
	buffer.length = ACPI_ALLOCATE_BUFFER;
	status_t status = acpi->get_irq_routing_table(device, &buffer);
	if (status != B_OK) {
		// simply not a bridge
		return;
	}

	TRACE("found irq routing table\n");

	uint64 value;
	pci_address pciAddress = parentAddress;
	if (evaluate_integer(acpi, device, "_ADR", value) == B_OK) {
		pciAddress.device = (uint8)(value >> 16);
		pciAddress.function = (uint8)value;
	} else {
		pciAddress.device = 0;
		pciAddress.function = 0;
	}

	if (!rootBridge) {
		// Find the secondary bus number (the "downstream" bus number for the
		// attached devices) in the bridge configuration.
		uint8 secondaryBus = pci->read_pci_config(pciAddress.bus,
			pciAddress.device, pciAddress.function, PCI_secondary_bus, 1);
		if (secondaryBus == 255) {
			// The bus below this bridge is inactive, nothing to do.
			return;
		}

		// The secondary bus cannot be the same as the current one.
		if (secondaryBus == parentAddress.bus) {
			dprintf("invalid secondary bus %u on primary bus %u,"
				" can't configure irq routing of devices below\n",
				secondaryBus, parentAddress.bus);
			return;
		}

		// Everything below is now on the secondary bus.
		pciAddress.bus = secondaryBus;
	}

	irq_routing_entry irqEntry;
	acpi_pci_routing_table* acpiTable = (acpi_pci_routing_table*)buffer.pointer;
	while (acpiTable->Length) {
		acpi_handle source;

		bool noSource = acpiTable->Source[0] == '\0';
			// The above line would be correct according to specs...
		noSource = acpiTable->SourceIndex != 0;
			// ... but we use this one as there seem to be quirks where
			// a source is indicated but not actually present. With a source
			// index != 0 a GSI is generally indicated.

		if (noSource
			|| acpi->get_handle(NULL, acpiTable->Source, &source) == B_OK) {

			irqEntry.device_address = acpiTable->Address;
			irqEntry.pin = acpiTable->Pin;
			irqEntry.source = noSource ? NULL : source;
			irqEntry.source_index = acpiTable->SourceIndex;
			irqEntry.pci_bus = pciAddress.bus;
			irqEntry.pci_device = (uint8)(acpiTable->Address >> 16);

			// resolve any link device so we get a straight GSI in all cases
			if (noSource) {
				// fixed GSI already
				irqEntry.irq = irqEntry.source_index;
				irqEntry.polarity = B_LOW_ACTIVE_POLARITY;
				irqEntry.trigger_mode = B_LEVEL_TRIGGERED;
			} else {
				irq_descriptor irqDescriptor;
				status = configure_link_device(acpi, source, irqDescriptor);
				if (status != B_OK) {
					dprintf("failed to configure link device\n");
					irqEntry.irq = 0;
				} else {
					irqEntry.irq = irqDescriptor.irq;
					irqEntry.polarity = irqDescriptor.polarity;
					irqEntry.trigger_mode = irqDescriptor.trigger_mode;
				}
			}

			if (irqEntry.irq != 0) {
				if (update_pci_info_for_entry(pci, irqEntry) != B_OK) {
					// Note: This isn't necesarily fatal, as there can be many
					// entries in the table pointing to disabled/optional
					// devices. Also they can be used to describe the full actual
					// wireing regardless of the presence of devices, in which
					// case many entries won't have matches.
#ifdef TRACE_PRT
					dprintf("didn't find a matching PCI device for irq entry,"
						" can't update interrupt_line info:\n");
					print_irq_routing_entry(irqEntry);
#endif
				} else
					table->PushBack(irqEntry);
			}
		}

		acpiTable = (acpi_pci_routing_table*)((uint8*)acpiTable
			+ acpiTable->Length);
	}

	free(buffer.pointer);

	// recurse down to the child devices
	acpi_data pathBuffer;
	pathBuffer.pointer = NULL;
	pathBuffer.length = ACPI_ALLOCATE_BUFFER;
	if (acpi->ns_handle_to_pathname(device, &pathBuffer) != B_OK) {
		dprintf("failed to resolve handle to path\n");
		return;
	}

	char childName[255];
	void* counter = NULL;
	while (acpi->get_next_entry(ACPI_TYPE_DEVICE, (char*)pathBuffer.pointer,
		childName, sizeof(childName), &counter) == B_OK) {

		acpi_handle childHandle;
		status = acpi->get_handle(NULL, childName, &childHandle);
		if (status != B_OK) {
			dprintf("failed to get handle to child \"%s\"\n", childName);
			continue;
		}

		TRACE("recursing down to child \"%s\"\n", childName);
		read_irq_routing_table_recursive(acpi, pci, childHandle, pciAddress,
			table, false);
	}

	free(pathBuffer.pointer);
}


status_t
read_irq_routing_table(acpi_module_info* acpi, IRQRoutingTable* table)
{
	char rootPciName[255];
	acpi_handle rootPciHandle;
	rootPciName[0] = 0;
	status_t status = acpi->get_device(kACPIPciRootName, 0, rootPciName, 255);
	if (status != B_OK)
		return status;

	status = acpi->get_handle(NULL, rootPciName, &rootPciHandle);
	if (status != B_OK)
		return status;

	// We reset the structure to 0 here. Any failed evaluation means default
	// values, so we don't have to do anything in the error case.
	pci_address rootPciAddress;
	memset(&rootPciAddress, 0, sizeof(pci_address));

	uint64 value;
	if (evaluate_integer(acpi, rootPciHandle, "_SEG", value) == B_OK)
		rootPciAddress.segment = (uint8)value;
	if (evaluate_integer(acpi, rootPciHandle, "_BBN", value) == B_OK)
		rootPciAddress.bus = (uint8)value;

	pci_module_info* pci;
	status = get_module(B_PCI_MODULE_NAME, (module_info**)&pci);
	if (status != B_OK) {
		// shouldn't happen, since the PCI module is a dependency of the
		// ACPI module and we shouldn't be here at all if it wasn't loaded
		dprintf("failed to get PCI module!\n");
		return status;
	}

	read_irq_routing_table_recursive(acpi, pci, rootPciHandle, rootPciAddress,
		table, true);

	put_module(B_PCI_MODULE_NAME);
	return table->Count() > 0 ? B_OK : B_ERROR;
}


static status_t
read_irq_descriptor(acpi_module_info* acpi, acpi_handle device,
	bool readCurrent, irq_descriptor* descriptor)
{
	acpi_data buffer;
	buffer.pointer = NULL;
	buffer.length = ACPI_ALLOCATE_BUFFER;

	status_t status;
	if (readCurrent)
		status = acpi->get_current_resources(device, &buffer);
	else
		status = acpi->get_possible_resources(device, &buffer);

	if (status != B_OK) {
		dprintf("failed to read %s resources for irq\n",
			readCurrent ? "current" : "possible");
		free(buffer.pointer);
		return status;
	}

	descriptor->irq = 0;
	acpi_resource* resource = (acpi_resource*)buffer.pointer;
	while (resource->Type != ACPI_RESOURCE_TYPE_END_TAG) {
		switch (resource->Type) {
			case ACPI_RESOURCE_TYPE_IRQ:
			{
				acpi_resource_irq& irq = resource->Data.Irq;
				if (irq.InterruptCount < 1) {
					dprintf("acpi irq resource with no interrupts\n");
					break;
				}

				descriptor->irq = irq.Interrupts[0];
				descriptor->shareable = irq.Sharable != 0;
				descriptor->trigger_mode = irq.Triggering == 0
					? B_LEVEL_TRIGGERED : B_EDGE_TRIGGERED;
				descriptor->polarity = irq.Polarity == 0
					? B_HIGH_ACTIVE_POLARITY : B_LOW_ACTIVE_POLARITY;

#ifdef TRACE_PRT
				dprintf("acpi irq resource (%s):\n",
					readCurrent ? "current" : "possible");
				dprintf("\ttriggering: %s\n",
					irq.Triggering == 0 ? "level" : "edge");
				dprintf("\tpolarity: %s active\n",
					irq.Polarity == 0 ? "high" : "low");
				dprintf("\tsharable: %s\n", irq.Sharable != 0 ? "yes" : "no");
				dprintf("\tcount: %u\n", irq.InterruptCount);
				if (irq.InterruptCount > 0) {
					dprintf("\tinterrupts:");
					for (uint16 i = 0; i < irq.InterruptCount; i++)
						dprintf(" %u", irq.Interrupts[i]);
					dprintf("\n");
				}
#endif
				break;
			}

			case ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
			{
				acpi_resource_extended_irq& irq = resource->Data.ExtendedIrq;
				if (irq.InterruptCount < 1) {
					dprintf("acpi extended irq resource with no interrupts\n");
					break;
				}

				descriptor->irq = irq.Interrupts[0];
				descriptor->shareable = irq.Sharable != 0;
				descriptor->trigger_mode = irq.Triggering == 0
					? B_LEVEL_TRIGGERED : B_EDGE_TRIGGERED;
				descriptor->polarity = irq.Polarity == 0
					? B_HIGH_ACTIVE_POLARITY : B_LOW_ACTIVE_POLARITY;

#ifdef TRACE_PRT
				dprintf("acpi extended irq resource (%s):\n",
					readCurrent ? "current" : "possible");
				dprintf("\tproducer: %s\n",
					irq.ProducerConsumer ? "yes" : "no");
				dprintf("\ttriggering: %s\n",
					irq.Triggering == 0 ? "level" : "edge");
				dprintf("\tpolarity: %s active\n",
					irq.Polarity == 0 ? "high" : "low");
				dprintf("\tsharable: %s\n", irq.Sharable != 0 ? "yes" : "no");
				dprintf("\tcount: %u\n", irq.InterruptCount);
				if (irq.InterruptCount > 0) {
					dprintf("\tinterrupts:");
					for (uint16 i = 0; i < irq.InterruptCount; i++)
						dprintf(" %u", irq.Interrupts[i]);
					dprintf("\n");
				}
#endif
				break;
			}
		}

		if (descriptor->irq != 0)
			break;

		resource = (acpi_resource*)((uint8*)resource + resource->Length);
	}

	free(buffer.pointer);
	return descriptor->irq != 0 ? B_OK : B_ERROR;
}


status_t
read_current_irq(acpi_module_info* acpi, acpi_handle device,
	irq_descriptor* descriptor)
{
	return read_irq_descriptor(acpi, device, true, descriptor);
}


status_t
read_possible_irq(acpi_module_info* acpi, acpi_handle device,
	irq_descriptor* descriptor)
{
	return read_irq_descriptor(acpi, device, false, descriptor);
}


status_t
set_current_irq(acpi_module_info* acpi, acpi_handle device,
	const irq_descriptor* descriptor)
{
	acpi_data buffer;
	buffer.pointer = NULL;
	buffer.length = ACPI_ALLOCATE_BUFFER;

	status_t status = acpi->get_current_resources(device, &buffer);
	if (status != B_OK) {
		dprintf("failed to read current resources for irq\n");
		return status;
	}

	bool irqWritten = false;
	acpi_resource* resource = (acpi_resource*)buffer.pointer;
	while (resource->Type != ACPI_RESOURCE_TYPE_END_TAG) {
		switch (resource->Type) {
			case ACPI_RESOURCE_TYPE_IRQ:
			{
				acpi_resource_irq& irq = resource->Data.Irq;
				if (irq.InterruptCount < 1) {
					dprintf("acpi irq resource with no interrupts\n");
					break;
				}

				irq.Triggering
					= descriptor->trigger_mode == B_LEVEL_TRIGGERED ? 0 : 1;
				irq.Polarity
					= descriptor->polarity == B_HIGH_ACTIVE_POLARITY ? 0 : 1;
				irq.Sharable = descriptor->shareable ? 0 : 1;
				irq.InterruptCount = 1;
				irq.Interrupts[0] = descriptor->irq;

				irqWritten = true;
				break;
			}

			case ACPI_RESOURCE_TYPE_EXTENDED_IRQ:
			{
				acpi_resource_extended_irq& irq = resource->Data.ExtendedIrq;
				if (irq.InterruptCount < 1) {
					dprintf("acpi extended irq resource with no interrupts\n");
					break;
				}

				irq.Triggering
					= descriptor->trigger_mode == B_LEVEL_TRIGGERED ? 0 : 1;
				irq.Polarity
					= descriptor->polarity == B_HIGH_ACTIVE_POLARITY ? 0 : 1;
				irq.Sharable = descriptor->shareable ? 0 : 1;
				irq.InterruptCount = 1;
				irq.Interrupts[0] = descriptor->irq;

				irqWritten = true;
				break;
			}
		}

		if (irqWritten)
			break;

		resource = (acpi_resource*)((uint8*)resource + resource->Length);
	}

	if (irqWritten) {
		status = acpi->set_current_resources(device, &buffer);
		if (status != B_OK)
			dprintf("failed to set irq resources\n");
	} else {
		dprintf("failed to write requested irq into resources\n");
		status = B_ERROR;
	}

	free(buffer.pointer);
	return status;
}
