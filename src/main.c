// #include "d_string.h"
// #include "my_array.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

typedef struct {
  size_t length;
  ListNode* head;
} Stack ;

Stack* stack_from_array (int* array, int length) {
  if (length == 0) {return NULL;}
  ListNode* list = new_list(array[0]);
  ListNode* head = list;
  for (int i = 1; i < length; i++) {
    ListNode* new_head = new_list(array[i]);
    new_head->next = list;
    list = new_head;
  }
  ListNode* tail = list;
  Stack* stack = malloc(sizeof(Stack)); 
  stack->length = length;
  stack->head = list;
  return stack;
}

void push (Stack* stack, int val) {
  if (stack->head == NULL) {
    stack->head = new_list(val);
    return;
  }
  ListNode* new_node = new_list(val);
  new_node->next = stack->head;
  stack->head = new_node;
  stack->length = stack->length + 1;
}

int pop (Stack* stack) {
  if (stack->head == NULL) {return -1;}
  ListNode* head = stack->head;
  stack->head = stack->head->next;
  stack->length = stack->length - 1;
  int value = head->val;
  free(head);
  return value;
}

int peek (Stack* stack) {
  if (stack->head == NULL) {
    return -1;
  }
  return stack->head->val;
}

void print_stack (Stack* stack) {
  print_list(stack->head);
}

int main(int argc, char **argv) {
  // int array[15] = {4,6,8, 12, 14, 15, 16, 17, 25, 27, 35, 46, 52, 55, 62};
  int array[15] = {45, 23, 62,  58, 38, 8543, 734, 85,
                   34, 54, 856, 27, 55, 9375, 845};
  int length = sizeof(array) / sizeof(int);
  // head_and_tail_from_array returns tail and modifies list in place
  Stack* stack = stack_from_array(array, length);
  int val = pop(stack);
  push(stack, 14555);
  print_stack(stack);
  printf("%d\n", peek(stack));

}
