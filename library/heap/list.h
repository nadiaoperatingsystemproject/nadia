#ifndef NOS_LIST_HEAP_H
#define NOS_LIST_HEAP_H
#include "../../kernel/include/kernel.h"
void init_heap_list(struct heap_s_list* list);
void* add_node_heap_list(struct heap_s_list* list, struct heap_s* node);
void *insert_before_node_heap_list(struct heap_s_list* list, struct heap_s* node,	
 struct heap_s* elem);
void *insert_after_node_heap_list(struct heap_s_list* list, struct heap_s* node,
 struct heap_s* elem);
void remove_node_heap_list(struct heap_s_list* list, struct heap_s* node);
int find_node_heap_list(struct heap_s_list* list, struct heap_s* node);
void* ordered_heap_list(struct heap_s_list* list);
#endif