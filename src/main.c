// #include "d_string.h"
// #include "my_array.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
  int val;
  struct ListNode* next;
};

typedef struct ListNode ListNode;

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

int main(int argc, char **argv) {
  // int array[15] = {4,6,8, 12, 14, 15, 16, 17, 25, 27, 35, 46, 52, 55, 62};
  int array[15] = {45, 23, 62,  58, 38, 8543, 734, 85,
                   34, 54, 856, 27, 55, 9375, 845};
  int length = sizeof(array) / sizeof(int);
  ListNode* list = list_from_array(array, length);
  ListNode* head = list;
  // printf("%lu\n", get_length(list));
  // print_list(list);
  // prepend(list, -1111);
  // append(list, 16788);
  // add(list, 77777);
  // print_list(list);
  // printf("%lu\n", get_length(list));
  // ListNode* new_list = get_index(list, 5);
  // printf("%d\n", new_list->val);
  // printf("%lu\n", get_length(new_list));
  // insert_at(list, 14, -77777);
  // print_list(list);
  // remove_head(list);
  remove_at(list, 3);
  print_list(list);
  remove_at(list, 13);
  print_list(list);
  printf("%lu\n", get_length(list));
  // for (int i = 0; i < length; i++) {
  //   printf("%d\n", array[i]);
  // }
  // printf("%d\n", index);
}
