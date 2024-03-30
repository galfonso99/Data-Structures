#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dl_list_node {
    int val;
    struct dl_list_node *prev;
    struct dl_list_node *next;
};
typedef struct dl_list_node dl_list_node;

dl_list_node* new_list (int val);

dl_list_node* list_from_array (int* array, int length); 

void print_list (dl_list_node* list); 
#endif
