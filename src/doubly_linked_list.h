#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int val;
    struct node *prev;
    struct node *next;
};
typedef struct node node;

typedef struct {
    int length;
    node *head;
    node *tail;
} linked_list;

node* create_node (int val); 

linked_list* list_from_array (int* array, int length); 


void print_list (linked_list * list); 

void print_head (node *head); 


void prepend(linked_list *list, int val); 

node * append (linked_list *list, int val); 

node* walk_list (linked_list *list, int index); 

int get (linked_list *list, int index); 


void add_first_node (linked_list *list, int value); 

void insert_at (linked_list *list, int index, int value); 

int remove_value (linked_list *list, int value);

void remove_back (linked_list *list); 

void remove_at (linked_list *list, int index); 

void dl_list_driver (); 

#endif
