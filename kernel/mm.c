/**
* Nadia OS descriptor file .c
*
* This file describe 
*
* @author : kabong freddy
*/

/**
*
*		PAGE TABLE STRUCTURE / PAGE DIRECTORY STRUCTURE
*		===============================================
*
*		+---------------------------+---------------+---------------------------+
*		| 31 |				   | 12 | 11 |   	| 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
*		+---------------------------+---------------+---------------------------+
*		|							|				|   |   | P | P | U | R |   |
*		+		base address		+	reserved	+ D + A + C + W + / + / + P +
*		|							|				|   |   | D | T | S | W |   |
*		+---------------------------+---------------+---------------------------+
*
*
*		DESCRIPTION
*		===========
*
*		BIT 0: 
*		BIT 1: 
*		BIT 2: 
*		BIT 3: 
*		BIT 4: 
*		BIT 5: 
*		BIT 6: 
*		BIT 7-11: 0
*		BIT 11-31: 
*
*
*/


#ifndef NOS_MEMORY
#define NOS_MEMORY
#define NOS_BITMAP
#define NOS_PAGING
#define NOS_HEAP
#include "include/i386/memory.h"
#include "include/kprint.h"
#include "include/kernel.h"
#include "../library/math.h"
#include "../library/list.h"
#include "../library/heap/list.h"
#include "../include/string.h"
#include "../include/assert.h"
#include "../include/io.h"

#endif

/**
*
*	+-----------------------------------------------------------+
*	|															|	
*	+	BITMAP'S FUNCTIONS				+						+
*	|															|
*	+-----------------------------------------------------------+
*
*/

extern struct mem_struct mem;
struct mem_struct* mem_info = &mem;
extern unsigned int end;
area_list_t* free_area;
area_list_t* area_used;
area_s_t* current_area = NULL;
unsigned int displacement = (unsigned int) &end ;
unsigned int cur_pos = 0;
page_s_t *page_dir = NULL;
page_s_t *currentdir = NULL;
page_s_t *page_table = NULL;
unsigned int* mem_map;
unsigned int* mem_vm_map;
as_map_t* current_as=NULL;
as_map_t *kernel_as = NULL;
as_map_t *buffer_as = NULL;
as_map_t *user_as = NULL;
as_map_t *heap_as = NULL;

unsigned int header_heap = 0;

void setbit(unsigned int* b_map,unsigned int addr){
	int frame = addr >> 12;
	int index = frame >> 5;
	int offset = frame % (1 << 5);
	b_map[index] |=  (0x1 << offset);
}

unsigned int testbit(unsigned int* b_map,unsigned int addr){
	int frame = addr >> 12;
	int index = frame >> 5;
	int offset = frame % (1 << 5);
	return b_map[index] & (0x1 << offset);
}

void clearbit(unsigned int* b_map,unsigned int addr){
	int frame = addr >> 12;
	int index = frame >> 5;
	int offset = frame % (1 << 5);
	b_map[index] &= ~(0x1 << offset);
}


/**
*
*	+-----------------------------------------------------------+
*	|															|	
*	+	STATIC AND DYNAMIC ALLOCATION'S FUNCTIONS	+			+
*	|															|
*	+-----------------------------------------------------------+
*
*/

int real_alloc_ap(size_t offset, unsigned int align){
	int tmp;
	if(align == 1 && (displacement & 0xFFFFF000))
		displacement = (displacement%0x1000 != 0)?(displacement & 0xFFFFF000) + 0x1000: displacement;
	tmp = displacement;
	displacement += offset;
	return tmp;
}

int *alloc(size_t offset){
	return (int*) real_alloc_ap(offset,0);
}

int *alloc_a(size_t offset){
	return (int*) real_alloc_ap(offset,1);
}

unsigned int get_free_frame(void){
	unsigned int np_byte =  mem.n_pages >> 5;
	for (unsigned int i = 0; i < np_byte; ++i)
		if (mem_map[i] != 0xFFFFFFFF)
			for(unsigned int j = 0; j < BIT_SIZE; j++)
				if(!(mem_map[i] & (0x1 << j))){
					setbit(mem_map,(i*BIT_SIZE+j)<<12);
					return ((i*BIT_SIZE+j)<<12);
				}
	return 0;
}

unsigned int get_free_vm_frame(void){
	unsigned int np_byte =  mem.n_vm_pages >> 5;
	unsigned int _vm = 0;
	for (unsigned int i = 0; i < np_byte; ++i)
		if (mem_vm_map[i] != 0xFFFFFFFF)
			for(unsigned int j = 0; j < BIT_SIZE; j++)
				if(!(mem_vm_map[i] & (0x1 << j))){
					_vm = (i*BIT_SIZE+j)<<12;
					setbit(mem_vm_map,_vm);
					return _vm + mem_info->vm_start_addr;
				}

	return 0;
}

int free_frame(unsigned int address){
	if(!testbit(mem_map,address))
		return 0;
	clearbit(mem_map,address);
	return address;
}

void copytablepage(page_s_t* to, const page_s_t* from){
	
}


void fragment_area(as_map_t* as, area_s_t* h, unsigned int size){
	area_s_t* chunk;
	unsigned int ar = (unsigned int) h + size;
	chunk = (area_s_t*) ar;
	chunk->start_addr = (unsigned int) chunk + sizeof(area_s_t);
	chunk->size = h->size - size;
	chunk->flags = 0x7;
	chunk->attribute = MEM_ATTR_NO;
	insert_after_node_list(as->list_f,h,chunk);
}

area_s_t* get_free_area(as_map_t* as, unsigned int size){
	// size is in page
	area_s_t* chunk = as->list_f->next;
	area_s_t* phy = NULL;
	
	// best fit
	while(chunk!=(area_s_t*)as->list_f){
		if(chunk->size >= size){
			phy = chunk;
			break;
		}
		chunk = chunk->next;
	}
	if(!phy)
		return NULL;
	if(phy->size >= size+PAGE_SIZE)
		fragment_area(as, phy,size);
	remove_node_list(as->list_f, phy);
	return phy;
}

// // unsigned int krealloc_real(unsigned int addr, unsigned int size){
	
// // }

// // allocate area space

int m_malloc_real(as_map_t* as, page_s_t* dir, int size, unsigned int flags){
	// check size
	if(size<=0){
		kprint ("\n size is null or negative");
		abort();
	}
	// create address space
	PAGING_OFF();
	page_s_t* pte = get_page_table(dir,as->start);
	if(!pte)
		pte = put_page_table(dir,as->start);
	put_page(dir,as->start,get_free_frame(),flags);
	PAGING_ON();
	return as->start;
}

// // Allocate virtual address space

int k_malloc(as_map_t* as, int size){
	return 	m_malloc(as, size, 0x3);
}

int k_malloc_sh(as_map_t* as, int size){
	return 	m_malloc_shared(as, size, 0x3);
}

int k_malloc_res(as_map_t* as, int size){
	return 	m_malloc_res(as, size, 0x3);
}

int m_malloc(as_map_t* as, int size, unsigned int flags){
	return 	smalloc(as, 0,size, MEM_ATTR_NO, flags);
}

int m_malloc_a(as_map_t* as, int size, unsigned int flags){
	return 	smalloc(as, 1,size, MEM_ATTR_NO, flags);
}

int m_malloc_shared(as_map_t* as, int size, unsigned int flags){
	return	smalloc(as, 0,size, MEM_ATTR_SHARED, flags);
}

int m_malloc_res(as_map_t* as, int size, unsigned int flags){
	return	smalloc(as, 0,size, MEM_ATTR_RESIDENT, flags);
}

int smalloc(as_map_t* as, int align, int size, unsigned int attribute,unsigned int flags){
	if(size<=0){
		kprint("\n Size is NULL or negative");
		abort();
	}
	unsigned int np = divround((size+sizeof(area_s_t)), PAGE_SIZE);
	unsigned int resize = !align?np*PAGE_SIZE:(np+1)*PAGE_SIZE;
	as->end += resize+sizeof(area_s_t);
	if(as->end>=as->limit)
		return 0;
	area_s_t* area;
	if(!current_as)
		current_as = as;
	if(resize<=(as->limit - as->start)){
		//find free address space
		sm:
		area = get_free_area(as,resize);
		if (!area)
		{
			area = (area_s_t*)m_malloc_real(as, currentdir,resize,0x7);
			area->npages = divround((as->size - sizeof(area_s_t)),PAGE_SIZE);
			area->size = area->npages*PAGE_SIZE;
			area->count = 0;
			area->attribute = MEM_ATTR_NO;
			add_node_list(as->list_f, area);
			goto sm;
		}
		//update virtual space
		area->start_addr = !align?(unsigned int) area + sizeof(area_s_t):(((unsigned int) area)&0xFFFFF000)+0x1000;
		area->size = resize - sizeof(area_s_t);
		area->npages = np;
		area->attribute = attribute;
		area->flags = flags;
		area->count = 1;
		current_area = area;
		as->end -= sizeof(area_s_t);
		memset((unsigned char*) area->start_addr, 0,PAGE_SIZE-sizeof(area_s_t));
		add_node_list(as->list_u, area);
		mem_info->remain_vm_pages -= area->npages;
		mem_info->remain_vm_size -= area->size;
		mem_info->used += area->size;
		return area->start_addr;
	}
	return 0;
}


int vm_malloc(as_map_t* as, unsigned int size, unsigned int attribute){
	unsigned int r_size = 0, min_size=0,
	n_blk_require = 0;
	header_heap = (unsigned int) divround(sizeof(heap_s_t), mem_info->min_vm_blocksize);
	header_heap *= mem_info->min_vm_blocksize;
	n_blk_require = divround(size,mem_info->min_vm_blocksize); 
	size = mem_info->min_vm_blocksize*n_blk_require;
	min_size = header_heap+mem_info->min_vm_blocksize;
	if((r_size = header_heap+size)<min_size)
		r_size = min_size;
	switch_as(as);
	heap_s_t* vm_heap = get_free_heap(current_as, r_size, attribute);
	if (!vm_heap)
		return NULL;
	add_node_heap_list(current_as->heap_u, vm_heap);
	return vm_heap->start_addr;
}

// int kfree_real(page_s_t* dir, unsigned int attribute, area_s_t* vm){
	
// 	if (do_no_page((unsigned int)vm))
// 	{
// 		/* code */
// 		kprint("\n address %p is not valid",vm);
// 		abort();
// 	}
	
// 	remove_node_list(area_used, &vm->list);

// 	mem_info->remain_vm_size += vm->size;
// 	mem_info->used -= vm->size;
	
// 	return (int) vm;
// }

// int kfree(void* vm){
// 	return sfree(vm, MEM_ATTR_NO);
// }

// int kfree_shared(void* vm){
// 	return sfree(vm, MEM_ATTR_SHARED);
// }

// int kfree_res(void* vm){
// 	return sfree(vm, MEM_ATTR_RESIDENT);
// }

// int sfree(void* vm, unsigned int attribute){
// 	if(!vm){
// 		kprint("\n virtual address space is NULL");
// 		abort();
// 	}
// 	unsigned int v = (unsigned int) vm - sizeof(area_s_t);
// 	area_s_t* fa = (area_s_t*) v;
// 	kprint("\n vm is %x ", v);
// 	int freed = kfree_real(currentdir, attribute,fa);
// 	if(!freed){
// 		kprint("\n violation memory");
// 		abort();
// 	}
// 	add_node_list(free_area, &fa->list);
// 	// fusion area
// 	return v;
// }

// unsigned int krealloc(area_s_t* vm, int size){

// }

/**
*
*	+-----------------------------------------------------------+
*	|															|	
*	+			PAGE FAULT FUNCTIONS				+			+
*	|															|
*	+-----------------------------------------------------------+
*
*/

int do_no_page(unsigned int address){
	unsigned int addr = address >> 12;
	if (addr>=(VM_START >> 12) && addr<0xFFFFF)
		return 0;
	return 1;
}

void put_page(page_s_t* dir, unsigned int vm, unsigned int address, unsigned int flags){
	// test if page table present
	
	page_s_t* page = get_page_table(dir, vm);
	page->present = flags & 0x1;
	page->writable = (flags&(1<<1)) >> 1;
	page->user = (flags&(1<<2)) >> 2;
	page->address = address >> 12;
	mem_info->count_pages--;
	memset((unsigned char*) (page->address << 12), 0,0x1000);
}

void do_wr_page(unsigned int address){
	kprint("\n Page %X not writable!", address);
	cli;
	asm volatile ("hlt"::);
}

void do_usr_page(unsigned int address){
	kprint("\n Premission denie in page %X ", address);
	cli;
	asm volatile ("hlt"::);
}

void do_rsvd_page(unsigned int address){
	kprint("bad translation for the linear address %X not present!", address);
	cli;
	asm volatile ("hlt"::);
}

void do_intr_fetch(unsigned int address){
	kprint("Page %X is not accessible!", address);
	cli;
	asm volatile ("hlt"::);
}


page_s_t* get_page_table(page_s_t* dir, unsigned int address){
	page_s_t* tmp;
	tmp = &dir[address >> 22];
	if(tmp->address)
		return (page_s_t*)((tmp->address << 12)+ ((address >> 12)%1024)*sizeof(page_s_t));
	return 0;
}

page_s_t* put_page_table(page_s_t* dir, unsigned int address){
	unsigned int pt = 0;
	page_s_t* tmp;
	if(!(pt = get_free_frame())){
		kprint("\n no page found");
		abort();
		return (page_s_t*) 0;
	}
	memset((unsigned char*) pt, 0,0x1000);
	tmp = &dir[address >> 22];
	tmp->present = 1;
	tmp->writable = 1;
	tmp->user = 1;
	tmp->address = pt >> 12;
	return (page_s_t*) pt;
}

/**
*
*	+-----------------------------------------------------------+
*	|															|	
*	+			INIT PAGING FUNCTIONS				+			+
*	|															|
*	+-----------------------------------------------------------+
*
*/



static void do_idty_page(page_s_t *pte){

	/**	identity map memory */
	page_s_t* tmp, *dir;
	for (int i = 0; i < VM_START; i+=0x1000)
	{
		/* code */
		unsigned int n = i >> 12;
		dir = &pte[n >> 10];
		tmp = (page_s_t*) (((dir->address) << 12) + (n%1024)*sizeof(page_s_t));
		tmp->present = 1;
		tmp->writable = 1;
		tmp->user = 0;
		tmp->address = n;
		mem_info->count_pages--;
		setbit(mem_map,i);
	}
}


void switch_pd(page_s_t* pd){
	currentdir = pd;
	asm volatile("mov %0, %%cr3"::"r"(pd));
}

void init_mm_map(void){

	// Map memory fix
	mem_info->min_vm_blocksize = 0x4;
	mem_info->n_pages = (mem_info->higher >> 12);
	mem_info->count_pages = mem_info->n_pages;
	mem_map = alloc_a(sizeof(unsigned int)*((mem_info->n_pages & 0xFFFFFFe0) >> 5)+mem_info->n_pages%(1<<5));
	memset((unsigned char*)mem_map , 0, sizeof(page_s_t)*1024);
	// allocate memory space for page directory
	page_dir = (page_s_t*) alloc_a(sizeof(page_s_t)*1024);
	memset((unsigned char*)page_dir , 0, sizeof(page_s_t)*1024);

	for(int i = 0; i < ((VM_START>>22)+1); i ++){
		//Allocate page table in memory
		unsigned int tmp = (unsigned int) alloc_a(sizeof(page_s_t)*1024);
		memset((unsigned char*)tmp , 0, sizeof(page_s_t)*1024);
		page_s_t* dir = &page_dir[i];
		dir->address = tmp >> 12;
		dir->user = 1;
		dir->writable = 1;
		dir->present = 1;
	}
	kernel_as = (as_map_t *) alloc(sizeof(as_map_t));
	buffer_as = (as_map_t *) alloc(sizeof(as_map_t));
	user_as = (as_map_t *) alloc(sizeof(as_map_t));
	heap_as = (as_map_t *) alloc(sizeof(as_map_t));
	memset((unsigned char*)kernel_as , 0, sizeof(as_map_t));
	memset((unsigned char*)buffer_as , 0, sizeof(as_map_t));
	memset((unsigned char*)user_as , 0, sizeof(as_map_t));
	memset((unsigned char*)heap_as , 0, sizeof(as_map_t));
	// init free and used area kernel
	kernel_as->list_f = (area_list_t*) alloc(sizeof(area_list_t));
	kernel_as->list_u = (area_list_t*) alloc(sizeof(area_list_t));
	kernel_as->start = S_KERNEL_OFFSET;
	kernel_as->end = kernel_as->start;
	kernel_as->limit = END_KERNEL_OFFSET;
	kernel_as->size = current_as->limit - current_as->start;
	init_list(kernel_as->list_f);
	init_list(kernel_as->list_u);
	init_heap_list(kernel_as->heap_f);
	init_heap_list(kernel_as->heap_u);
	// init free and used area buffer
	buffer_as->list_f = (area_list_t*) alloc(sizeof(area_list_t));
	buffer_as->list_u = (area_list_t*) alloc(sizeof(area_list_t));
	buffer_as->start = S_BUFFER;
	buffer_as->end = buffer_as->start;
	buffer_as->limit = END_BUFFER;
	kernel_as->size = kernel_as->limit - kernel_as->start;
	init_list(buffer_as->list_f);
	init_list(buffer_as->list_u);
	init_heap_list(buffer_as->heap_f);
	init_heap_list(buffer_as->heap_u);
	// init free and used area user
	user_as->list_f = (area_list_t*) alloc(sizeof(area_list_t));
	user_as->list_u = (area_list_t*) alloc(sizeof(area_list_t));
	user_as->start = S_U_OFFSET;
	user_as->end = user_as->start;
	user_as->limit = END_U_OFFSET;
	user_as->size = user_as->limit - user_as->start;
	init_list(user_as->list_f);
	init_list(user_as->list_u);
	user_as->heap_f = (heap_list_t*) alloc(sizeof(heap_list_t));
	user_as->heap_u = (heap_list_t*) alloc(sizeof(heap_list_t));
	init_heap_list(user_as->heap_f);
	init_heap_list(user_as->heap_u);
	// init free and used area heap
	heap_as->list_f = (area_list_t*) alloc(sizeof(area_list_t));
	heap_as->list_u = (area_list_t*) alloc(sizeof(area_list_t));
	heap_as->start = S_ADDR_HEAP;
	heap_as->end = heap_as->start;
	heap_as->limit = END_HEAP;
	heap_as->size = heap_as->limit - heap_as->start;
	init_list(heap_as->list_f);
	init_list(heap_as->list_u);
	heap_as->heap_f = (heap_list_t*) alloc(sizeof(heap_list_t));
	heap_as->heap_u = (heap_list_t*) alloc(sizeof(heap_list_t));
	init_heap_list(heap_as->heap_f);
	init_heap_list(heap_as->heap_u);

	//Aligment in 4096 bytes
	align();

	//Make identity memory

	do_idty_page(page_dir);

	//Aligment in 4096 bytes 
	align();

	mem_info->lower = displacement;
	mem_info->used = displacement;
	mem_info->remain_size = mem_info->higher - displacement;
	mem_info->remain_pages = divround(mem_info->remain_size,PAGE_SIZE);
	cur_pos = VM_START;
	mem_info->n_vm_pages = divround((mem_info->higher-cur_pos),PAGE_SIZE);
	mem_info->vm_size = mem_info->higher-cur_pos;
	mem_info->vm_start_addr = cur_pos;
	mem_info->remain_vm_size = mem_info->vm_size;

	/*	ENABLE PAGING  */
	switch_pd(page_dir);
	PAGING_ON();
	kprint("\n [+] PAGING ON \n");
}


/**
*
*	+-----------------------------------------------------------+
*	|															|	
*	+			MEMORY'S ONTROLLERS FUNCTIONS		+			+
*	|															|
*	+-----------------------------------------------------------+
*
*/
void align(void){
	displacement = (displacement & 0xFFFFFFFF)+0x1000;
}

// void dump_mem(void){

// }

void switch_as(as_map_t* as){
	current_as = as;
}