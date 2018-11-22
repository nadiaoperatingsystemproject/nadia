#ifndef NOS_LIST
#define NOS_LIST
#include "list.h"
#include "../../kernel/include/kprint.h"
#include "../../include/assert.h"
#endif

void init_heap_list(struct heap_s_list* list){
	list->next = (struct heap_s*)list;
	list->prev = (struct heap_s*)list;
	kprint("\n list %x next %x prev %x", list, list->next,list->prev);
}

void *add_node_heap_list(struct heap_s_list* list, struct heap_s* node){
	struct heap_s* head = list->next;
	struct heap_s* tail = list->prev;
	struct heap_s_list* nil = list;
	if(!node)
		return 0;
	node->next = head;
	if(head!=(struct heap_s*)nil)
		head->prev = node;
	if(head == (struct heap_s*)nil)
		list->prev = node;
	list->next = node;
	node->prev = (struct heap_s*)nil;
	return node;
}

void* insert_before_node_heap_list(struct heap_s_list* list, struct heap_s* node, struct heap_s* elem){
	if(!node || !elem)
		return (void*)-1;
	if(!find_node_heap_list(list,node)){
		kprint("\n not insert");
		return 0;
	}
	elem->next = node;
	elem->prev = node->prev;
	node->prev->next = elem;
	node->prev = elem;
	return elem;
}

void* insert_after_node_heap_list(struct heap_s_list* list, struct heap_s* node, struct heap_s* elem){
	if(!node || !elem)
		return (void*)-1;
	if(!find_node_heap_list(list,node)){
		kprint("\n not insert");
		return 0;
	}
	elem->next = node->next;
	elem->prev = node;
	node->next->prev = elem;
	node->next = elem;
	return elem;
}
void remove_node_heap_list(struct heap_s_list* list, struct heap_s* node){
	struct heap_s_list* nil = list;
	struct heap_s* head = list->next;
	if(head!=(struct heap_s*)nil){
		if(node->prev != (struct heap_s*)nil)
			node->prev->next = node->next;
		else
			list->next = node->next;
		if(node->next!=(struct heap_s*)nil)
			node->next->prev = node->prev;
		else
			list->prev = node->prev;
	}
}


int find_node_heap_list(struct heap_s_list* list, struct heap_s* node){
	struct heap_s* tmp = list->next;
	struct heap_s_list* nil = list;
	while(tmp!=(struct heap_s*)nil && tmp != node)
		tmp = tmp->next;
	return (node == (struct heap_s*)nil) ? 0 : (int)node;
}

void *ordered_heap_list(struct heap_s_list* list){
	
}