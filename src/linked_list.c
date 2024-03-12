#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

ListNode* new_list (int val) {
  ListNode* list = malloc(sizeof(ListNode));
  list->val = val;
  list->next = NULL;
  return list;
}

ListNode* list_from_array (int* array, int length) {
  if (length == 0) {return NULL;}
  ListNode* list = new_list(array[0]);
  ListNode* head = list;
  for (int i = 1; i < length; i++) {
    ListNode* next_node = new_list(-1);
    list->next = next_node;
    list = list->next;
    list->val = array[i];
  }
  return head;
}

void print_list (ListNode* list) {
  while (list != NULL) {
    printf("%d\n", list->val);
    list = list->next;
  }
}

size_t get_length (ListNode* list) {
  size_t count = 0;
  while (list != NULL) {
    count++;
    list = list->next;
  }
  return count;
}

void prepend (ListNode* list, int val) {
  ListNode* old_head = new_list(list->val);
  ListNode* tail = list->next;
  // Change the value of head to new_head (value passed in)
  list->val = val;
  // Now point this newly added head to to old_head
  list->next = old_head;
  old_head->next = tail;
}

void append (ListNode* list, int val) {
  while (list->next != NULL) {
    list = list->next;
  }
  ListNode* new_node = new_list(val);
  list->next = new_node;
}

// Adds a new node with given value after head and before tail
void add (ListNode* list, int val) {
  ListNode* tail = list->next;
  ListNode* new_node = new_list(val);
  list->next = new_node;
  new_node->next = tail;
}

ListNode* get_index (ListNode* list, int index) {
  for (int i = 0; i < index; i++) {
    list = list->next;
  }
  return list;
}

void insert_at(ListNode* list, int index, int val) {
  for (int i = 0; i < index-1; i++) {
    list = list->next;
  }
  ListNode* old_node = list->next;
  ListNode* inserted_node = new_list(val);
  list->next = inserted_node;
  inserted_node->next = old_node;
}

void remove_head (ListNode* node) {
  ListNode* tail = node->next;
  *node = *tail;
}

void remove_at(ListNode* list, int index) {
  for (int i = 0; i < index - 1; i++) {
    list = list->next;
  }
  ListNode* tail = list->next->next;
  list->next = tail;
}

