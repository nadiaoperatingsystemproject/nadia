#ifndef NOS_FREE
#define NOS_FREE
#define NOS_HEAP
#include "../kernel/include/i386/memory.h"
#include "../kernel/include/kprint.h"
#include "../include/string.h"
#include "../include/assert.h"
#include "../library/list.h"
#include "math.h"
#endif


extern struct mem_struct* mem_info;
extern area_s_t* current_as;

int free(void* addresse){
	if(!addresse){
		abort();
		return -1;
	}
	unsigned int addr = (unsigned int) addresse-sizeof(heap_s_t);
	heap_s_t* vm = (heap_s_t*) addr;
	if(vm = free_heap(current_as, vm)){
		//fusion block free if they are contigue

		return (int) vm;
	}
	return 0;
}