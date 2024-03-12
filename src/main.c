// #include "d_string.h"
// #include "my_array.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

ListNode* head_and_tail_from_array (ListNode* list, int* array, int length) {
  if (length == 0) {return NULL;}
  list->val = array[0];
  for (int i = 1; i < length; i++) {
    ListNode* next_node = new_list(-1);
    list->next = next_node;
    list = list->next;
    list->val = array[i];
  }
  return list;
}

void enqueue (ListNode **tail, int val) {
  (*tail)->next = new_list(val);
  (*tail) = (*tail)->next;
} 

void deque (ListNode* list) {
  *list = *(list->next);
}

int peek (ListNode* list) {
  return list->val;
}

int main(int argc, char **argv) {
  // int array[15] = {4,6,8, 12, 14, 15, 16, 17, 25, 27, 35, 46, 52, 55, 62};
  int array[15] = {45, 23, 62,  58, 38, 8543, 734, 85,
                   34, 54, 856, 27, 55, 9375, 845};
  int length = sizeof(array) / sizeof(int);
  ListNode* list = new_list(0);
  // head_and_tail_from_array returns tail and modifies list in place
  ListNode* tail = head_and_tail_from_array(list, array, length);
  // print_list(tail);
  // printf("%d\n", peek(list));
  enqueue(&tail, 537386);
  enqueue(&tail, -444837);
  deque(list);
  print_list(list);
}
