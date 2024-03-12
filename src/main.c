// #include "d_string.h"
// #include "my_array.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

typedef struct {
  size_t length;
  ListNode* head;
  ListNode* tail;
} Queue ;

Queue* queue_from_array (int* array, int length) {
  if (length == 0) {return NULL;}
  ListNode* list = new_list(array[0]);
  ListNode* head = list;
  for (int i = 1; i < length; i++) {
    ListNode* next_node = new_list(-1);
    list->next = next_node;
    list = list->next;
    list->val = array[i];
  }
  ListNode* tail = list;
  Queue* queue = malloc(sizeof(Queue)); 
  queue->length = length;
  queue->head = head;
  queue->tail = tail;
  return queue;
}

void enqueue (Queue* queue, int val) {
  if (queue->tail == NULL) {
    queue->head = new_list(val);
    queue->tail = queue->head;
    return;
  }
  ListNode* new_node = new_list(val);
  queue->tail->next = new_node;
  queue->tail = queue->tail->next;
  queue->length = queue->length + 1;
} 

int deque (Queue* queue) {
  if (queue->head == NULL) {return -1;}
  ListNode* head = queue->head;
  queue->head = queue->head->next;
  queue->length = queue->length - 1;
  int value = head->val;
  free(head);
  if (queue->length == 0) {
    queue->tail = NULL;
  }
  return value;
}

int peek (Queue* queue) {
  if (queue->head == NULL) {
    return -1;
  }
  return queue->head->val;
}

void print_queue (Queue* queue) {
  print_list(queue->head);
}

int main(int argc, char **argv) {
  // int array[15] = {4,6,8, 12, 14, 15, 16, 17, 25, 27, 35, 46, 52, 55, 62};
  int array[15] = {45, 23, 62,  58, 38, 8543, 734, 85,
                   34, 54, 856, 27, 55, 9375, 845};
  int length = sizeof(array) / sizeof(int);
  // head_and_tail_from_array returns tail and modifies list in place
  Queue* queue = queue_from_array(array, length);
  // print_list(tail);
  // printf("%d\n", peek(queue));
  enqueue(queue, 537386);
  enqueue(queue, -444837);
  // printf("%lu\n", queue->length);
  int a = deque(queue);
  int b = deque(queue);
  printf("%d\n", a);
  printf("%d\n", b);
  print_queue(queue);

}
