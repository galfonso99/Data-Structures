
#include "doubly_linked_list.h"
#include <stdlib.h>
#include <stdio.h>

dl_list_node* new_list (int val) {
  dl_list_node* list = malloc(sizeof(dl_list_node));
  list->val = val;
  list->next = NULL;
  return list;
}

dl_list_node* list_from_array (int* array, int length) {
  if (length == 0) {return NULL;}
  dl_list_node* list = new_list(array[0]);
  dl_list_node* head = list;
  for (int i = 1; i < length; i++) {
    dl_list_node* next_node = new_list(-1);
    list->next = next_node;
    list = list->next;
    list->val = array[i];
  }
  return head;
}

void print_list (dl_list_node* list) {
  while (list != NULL) {
    printf("%d\n", list->val);
    list = list->next;
  }
}
