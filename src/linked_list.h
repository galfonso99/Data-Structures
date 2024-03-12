#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stdlib.h>

struct ListNode {
  int val;
  struct ListNode* next;
};

typedef struct ListNode ListNode;

ListNode* new_list (int val);

ListNode* list_from_array (int* array, int length); 

void print_list (ListNode* list); 

size_t get_length (ListNode* list); 

void prepend (ListNode* list, int val); 

void append (ListNode* list, int val); 

// Adds a new node with given value after head and before tail
void add (ListNode* list, int val); 

ListNode* get_index (ListNode* list, int index); 

void insert_at(ListNode* list, int index, int val); 

void remove_head (ListNode* node); 

void remove_at(ListNode* list, int index); 

#endif

