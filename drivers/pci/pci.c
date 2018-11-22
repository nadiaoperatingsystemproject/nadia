
#include "pci.h"
__extern__ __void__ __kprint_video__(const char* str);
__extern__ __void__ __kernel_Put_Chr__(uint8_t, uint8_t );

uint32_t read_pci(pci_device_id_t* dev, uint16_t registerOffset){
	uint32_t id = setup_id(dev, registerOffset);
	uint32_t data_id;
	outl(__PCI_ADD_PORT__,id);
	data_id = inl(__PCI_DATA_PORT__);
	return data_id >>(8*(registerOffset % 4));
}

__void__ write_pci(pci_device_id_t* dev, uint16_t registerOffset, uint32_t data){
	uint32_t id = setup_id(dev, registerOffset);
	outl(__PCI_ADD_PORT__,id);
	outl(__PCI_DATA_PORT__, data);
}

uint32_t setup_id(pci_device_id_t* dev, uint16_t registerOffset){
	return (0x1 << 31) | setup_bus(dev) | setup_device(dev) | setup_function(dev) | (registerOffset & 0xFC);
}

uint16_t setup_bus(pci_device_id_t* dev){
	return (dev->bus_id & 0xFF) << 16;
}

uint16_t setup_device(pci_device_id_t* dev){
	return (dev->device & 0x1F) << 11;
}

uint16_t setup_function(pci_device_id_t* dev){
	return (dev->function & 0x07) << 8;
}


__static__ __void__ __set_pci_device_id__(pci_device_id_t* dev, uint16_t bus_id, uint16_t device, uint16_t function){
	dev->bus_id = bus_id;
	dev->device = device;
	dev->function = function;

	dev->devRegister.vendor_id = (uint16_t) read_pci(dev, 0x00);
	dev->devRegister.device_id = (uint16_t) read_pci(dev, 0x02);

	dev->devRegister.classcode.class_id = (uint8_t) read_pci(dev, 0x0b);
	dev->devRegister.classcode.subClass_id = (uint8_t) read_pci(dev, 0x0a);
	
	dev->devRegister.interface_id = (uint8_t) read_pci(dev, 0x09);

	dev->devRegister.revision = (uint8_t) read_pci(dev, 0x08);
	dev->devRegister.interrupt = read_pci(dev, 0x3C);
}

__static__ bool_t __pci_detect_device_function__(pci_device_id_t* dev, uint16_t registerOffset){
	return read_pci(dev, registerOffset) & (1<<7);
}

__extern__ __void__ __pci_detect_device__(__void__){
	uint32_t num_fn;
	pci_device_id_t dev;
	for (int bus = 0; bus < 1; ++bus)
	{
		/* code */
		for (int device = 0; device < 32; ++device)
		{
			/* code */
			dev.bus_id = bus;
			dev.device = device;
			dev.function = 0;
			num_fn = __pci_detect_device_function__(&dev,0x0E)?8:1;
			for (int function = 0; function < num_fn; ++function)
			{
				/* code */
				__set_pci_device_id__(&dev, bus, device, function);
				if (dev.devRegister.vendor_id == 0x0000 || dev.devRegister.vendor_id == 0xFFFF){
					break;
				}
				
				__kprint_video__("Bus ");
				__kprint_video__(__itoab__(bus&0xff, 16));
				__kprint_video__(", ");
				__kprint_video__("Device ");
				__kprint_video__(__itoab__(device&0xff, 16));
				__kprint_video__(", ");
				__kprint_video__("Function ");
				__kprint_video__(__itoab__(function&0xff, 16));
				__kprint_video__(", ");
				__kprint_video__("= Vendor ");
				__kprint_video__(__itoab__((dev.devRegister.vendor_id&0xff00)>>8, 16));
				__kprint_video__(__itoab__((dev.devRegister.vendor_id&0xff), 16));
				__kprint_video__(", ");
				__kprint_video__("Device ");
				__kprint_video__(__itoab__((dev.devRegister.device_id&0xff00)>>8, 16));
				__kprint_video__(__itoab__((dev.devRegister.device_id&0xff), 16));
				__kprint_video__("\n");
			}
		}
	}
}







