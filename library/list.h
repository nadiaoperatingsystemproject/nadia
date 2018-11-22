#ifndef NOS_LIST_H
#define NOS_LIST_H
#include "../kernel/include/kernel.h"
void init_list(struct area_s_list* list);
void* add_node_list(struct area_s_list* list, struct area_s* node);
void *insert_before_node_list(struct area_s_list* list, struct area_s* node,	
 struct area_s* elem);
void *insert_after_node_list(struct area_s_list* list, struct area_s* node,
 struct area_s* elem);
void remove_node_list(struct area_s_list* list, struct area_s* node);
int find_node_list(struct area_s_list* list, struct area_s* node);
void* ordered_list(struct area_s_list* list);
#endif