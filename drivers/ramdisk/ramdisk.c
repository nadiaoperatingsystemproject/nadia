
#ifndef NOS_INITRAMDISK
#define NOS_INITRAMDISK
#include "../../include/fs/fs.h"
#include "../../include/hd.h"
#include "../../include/assert.h"
#include "../../include/string.h"
#include "../../kernel/include/i386/memory.h"
#include "../../kernel/include/kprint.h"
#define ctlr_in()	1
#define ctlr_out()	1
#endif
/* ramdisk is an emulator of hard disk*/
#define VDISKSIZE	0x8000000
#define SECTORSIZE	512
struct vdisk
{
	unsigned int n_sect;
	unsigned char id;
	unsigned char serial;
	unsigned char *rdata;
};
struct vdisk dsk;
void *read_vdisk(unsigned int, unsigned int, unsigned char*);
void write_vdisk(unsigned int, unsigned int, unsigned char*);

void read_vb(unsigned int, unsigned int, unsigned char*);
void write_vb(unsigned int, unsigned int, unsigned char*);

void initrdisk(void){
	// clean virtual device
	// dsk->data = (unsigned char*) malloc(VDISKSIZE);
	// memset(dsk->data,0,VDISKSIZE);
	// //init fs in vdisk
	// 	// init bootsect
	
	// return;
}