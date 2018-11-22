#ifndef NOS_GLOBAL_H
#define NOS_GLOBAL_H
#define NULL			0x0

struct multiboot {
        unsigned long flags;
        unsigned long low_mem;
        unsigned long high_mem;
        unsigned long boot_device;
        unsigned long cmdline;
}__attribute__ ((packed));

struct mem_struct
{
	unsigned int higher;
	unsigned int lower;
	unsigned int used;
	unsigned int remain_pages;
	unsigned int remain_size;
	unsigned int n_pages;
	unsigned int n_vm_pages;
	unsigned int count_pages;
	unsigned int vm_size;
	unsigned int remain_vm_pages;
	unsigned int remain_vm_size;
	unsigned int vm_start_addr;
	unsigned int page_size;
	unsigned int min_vm_blocksize;
};

struct event
{
		
};

typedef struct event event_t;


struct graph{
	unsigned int width;
	unsigned int height;
	struct pos{
		int X;
		int Y;
	} pos;
	struct offset{
		int X;
		int Y;
	} offset;
	struct graph* parent;
	struct graph* children;
};

typedef struct graph graph_t;
#endif