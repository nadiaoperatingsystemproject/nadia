#ifndef NOS_MALLOC
#define NOS_MALLOC
#define NOS_HEAP
#include "math.h"
#include "../kernel/include/i386/memory.h"
#endif

extern struct mem_struct* mem_info;
extern as_map_t* heap_as;
extern as_map_t* current_as;

int malloc(unsigned int size){
	unsigned int vm;
	switch_as(heap_as);
	vm = vm_malloc(current_as,size,MEM_ATTR_NO);
	return vm;
}

int malloc_sh(unsigned int size){
	unsigned int vm;
	switch_as(heap_as);
	vm = vm_malloc(current_as,size,MEM_ATTR_SHARED);
	return vm;
}

int malloc_res(unsigned int size){
	unsigned int vm;
	switch_as(heap_as);
	vm = vm_malloc(current_as,size,MEM_ATTR_RESIDENT);
	return vm;
}