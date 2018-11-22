#ifndef NOS_LIST
#define NOS_LIST
#include "../library/list.h"
#include "include/kprint.h"
#endif

void init_list(struct area_s_list* list){
	list->next = (struct area_s*)list;
	list->prev = (struct area_s*)list;
	list->count = 0;
}

void *add_node_list(struct area_s_list* list, struct area_s* node){
	struct area_s* head = list->next;
	struct area_s* tail = list->prev;
	struct area_s_list* nil = list;
	if(!node)
		return 0;
	node->next = head;
	if(head!=(struct area_s*)nil)
		head->prev = node;
	if(head == (struct area_s*)nil)
		list->prev = node;
	list->next = node;
	node->prev = (struct area_s*)nil;
	list->count++;
	return node;
}

void* insert_before_node_list(struct area_s_list* list, struct area_s* node, struct area_s* elem){
	if(!node || !elem)
		return (void*)-1;
	if(!find_node_list(list,node)){
		kprint("\n not insert");
		return 0;
	}
	elem->next = node;
	elem->prev = node->prev;
	node->prev->next = elem;
	node->prev = elem;
	list->count++;
	return elem;
}

void* insert_after_node_list(struct area_s_list* list, struct area_s* node, struct area_s* elem){
	if(!node || !elem)
		return (void*)-1;
	if(!find_node_list(list,node)){
		kprint("\n not insert");
		return 0;
	}
	elem->next = node->next;
	elem->prev = node;
	node->next->prev = elem;
	node->next = elem;
	list->count++;
	return elem;
}
void remove_node_list(struct area_s_list* list, struct area_s* node){
	struct area_s_list* nil = list;
	struct area_s* head = list->next;
	if(head!=(struct area_s*)nil){
		if(node->prev != (struct area_s*)nil)
			node->prev->next = node->next;
		else
			list->next = node->next;
		if(node->next!=(struct area_s*)nil)
			node->next->prev = node->prev;
		else
			list->prev = node->prev;
		list->count--;
	}
}


int find_node_list(struct area_s_list* list, struct area_s* node){
	struct area_s* tmp = list->next;
	struct area_s_list* nil = list;
	while(tmp!=(struct area_s*)nil && tmp != node)
		tmp = tmp->next;
	return (node == (struct area_s*)nil) ? 0 : (int)node;
}

void *ordered_list(struct area_s_list* list){
	
}