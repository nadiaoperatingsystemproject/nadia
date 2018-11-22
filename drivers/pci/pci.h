#ifndef __PCI_H__
#define __PCI_H__ 
#include "../../include/types.h"
#include "../../include/io.h"
#include "../../include/string.h"

#define __PCI_DATA_PORT__			0xCFC
#define __PCI_ADD_PORT__			0xCF8



typedef struct __base_address_register_struct__{
	uint8_t space_indiator:1;
	uint8_t type;
	uint8_t prefetchable:1;
	uint32_t* address;
}base_address_register_t;

typedef struct __classCode_struct__{
	uint8_t class_id;
	uint8_t subClass_id;
	uint8_t profIf;
}classCode_t;

typedef struct __pci_device_register_struct__{
	uint16_t vendor_id;
	uint16_t device_id;

	uint16_t command;
	uint16_t status;

	classCode_t classcode;
	base_address_register_t bar;

	uint8_t interface_id;

	uint8_t revision;

	uint32_t interrupt;

}pci_device_register_t;

typedef struct __pci_device_id_struct__
{
	uint32_t port_base;

	uint16_t bus_id;
	uint16_t device;
	uint16_t function;

	pci_device_register_t devRegister;

}pci_device_id_t;

pci_device_id_t pci_device;

uint32_t read_pci(pci_device_id_t*, uint16_t);
__void__ write_pci(pci_device_id_t*, uint16_t, uint32_t);
uint32_t setup_id(pci_device_id_t*, uint16_t);
uint16_t setup_bus(pci_device_id_t*);
uint16_t setup_device(pci_device_id_t*);
uint16_t setup_function(pci_device_id_t*);

__void__ __init_pci_device__(__void__);
__static__ __void__ __set_pci_device_id__(pci_device_id_t*,uint16_t, uint16_t, uint16_t);
__static__ bool_t __pci_detect_device_function__(pci_device_id_t*, uint16_t);
__extern__ __void__ __pci_detect_device__(__void__);
#endif