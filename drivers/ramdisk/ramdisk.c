
#ifndef NOS_INITRAMDISK
#define NOS_INITRAMDISK
#include "../../include/fs/fs.h"
#include "../../include/hd.h"
#include "../../include/assert.h"
#include "../../include/string.h"
#include "../../kernel/include/i386/memory.h"
#include "../../kernel/include/kprint.h"
define ctlr_in()
define ctlr_out()
#endif
/* ramdisk is an emulator of hard disk*/
#define VDISKSIZE	0x8000000
#define SECTORSIZE	512
struct vdisk
{
	unsigned int n_sect;
	unsigned char id;
	unsigned char serial;
	unsigned char *data;
};
struct vdisk dsk;
void *read_vdisk(void);
void write_vdisk(void);

void read_vb(unsigned int, unsigned int, unsigned char*);
void write_vb(unsigned int, unsigned int, unsigned char*);

dev_t* initrdisk(void){
	// clean virtual device
	dsk->data = (dev_t*) malloc(VDISKSIZE);
	memset((unsigned char*) vdisk,0,VDISKSIZE);
	//init fs in vdisk
		// init bootsect
	
	return dsk;
}