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

typedef struct {
    int length;
    dl_list_node *head;
    dl_list_node *tail;
} linked_list;

dl_list_node* create_node (int val); 

linked_list* list_from_array (int* array, int length); 


void print_list (linked_list * list); 

void print_head (dl_list_node *head); 


void prepend(linked_list *list, int val); 

void append (linked_list *list, int val); 

dl_list_node* walk_list (linked_list *list, int index); 

int get (linked_list *list, int index); 


void add_first_node (linked_list *list, int value); 

void insert_at (linked_list *list, int index, int value); 


void remove_back (linked_list *list); 

void remove_at (linked_list *list, int index); 

void dl_list_driver (); 

#endif
