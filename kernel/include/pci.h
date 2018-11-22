/**
* Nadia OS descriptor file .h
*
* This file describe 
*
* @author : kabong freddy
*/

#ifndef NOS_PCI_H
#define NOS_PCI_H
#define PCI_CMD_PORT	0xCF8
#define PCI_DATA_PORT 	0xCFC

struct pci_register
{
	
};

unsigned int pci_read_8(struct pci_register*);
void pci_write_8(struct pci_register*);
unsigned int pci_read_16(struct pci_register*);
void pci_write_16(struct pci_register*);
unsigned int pci_read_32(struct pci_register*);
void pci_write_32(struct pci_register*);
#endif