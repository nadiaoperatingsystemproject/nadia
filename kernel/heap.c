#ifndef NOS_HEAP
#define NOS_HEAP
#include "include/i386/memory.h"
#include "include/kprint.h"
#include "../library/heap/list.h"
#include "../include/string.h"
#include "../include/assert.h"
#endif

extern struct mem_struct* mem_info;

extern area_s_t* current_area;

extern unsigned int header_heap;

heap_s_t* get_free_heap(as_map_t* as, unsigned int size, unsigned int attribute){
	heap_s_t *heap = NULL;
	heap_s_t *chunk = as->heap_f->next;
	if(size>as->size){
		return 0;
	}

	while(chunk != (heap_s_t*) as->heap_f){
		if(chunk->size >= size){
			heap = chunk;
			break;
		}
		chunk = chunk->next;
	}

	if(!heap)
		heap = kmalloc_heap(as,size,attribute);
	if(!heap)
		return 0;
	if(heap->size >= size+header_heap+mem_info->min_vm_blocksize)
		fragment_heap(as, heap, size);
	remove_node_heap_list(as->heap_f, heap);
	return heap;
}

void fragment_heap(as_map_t* as, heap_s_t* h, unsigned int size){
	heap_s_t* chunk;
	heap_s_t* tmp = as->heap_f->next;
	unsigned int s = size-header_heap;
	unsigned int ar = (unsigned int) h + size;
	chunk = (heap_s_t*) ar;
	chunk->start_addr = (unsigned int) chunk + header_heap;
	chunk->size = h->size - s;
	h->size = s;
	if(!insert_after_node_heap_list(as->heap_f,h,chunk)){
		kprint("\n insertion heap failed");
		abort();
	}
}

heap_s_t* kmalloc_heap(as_map_t* as, unsigned int size, unsigned int attribute){
	heap_s_t* heap;
	switch(attribute){
		case MEM_ATTR_NO:
		heap = (heap_s_t*) k_malloc(as, size);
		break;
		case MEM_ATTR_RESIDENT:
		heap = (heap_s_t*) k_malloc_res(as, size);
		break;
		case MEM_ATTR_SHARED:
		heap = (heap_s_t*) k_malloc_sh(as, size);
		break;
	}
	if(!heap)
		return 0;
	heap->start_addr = (unsigned int) heap + header_heap;
	heap->size = current_area->size - header_heap;
	add_node_heap_list(as->heap_f, heap);
	return heap;
}