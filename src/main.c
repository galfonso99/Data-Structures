// #include "d_string.h"
// #include "my_array.h"
// #include <stdlib>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  size_t length;
  size_t buffer;
  int *array;
} ArrayList;

// Methods to implement
// Push
// Pop
// Enqueue
// Deque
// Using an ArrayList we can implement a Queue by adding from the end and
// removing from the front and shifting all vales to the left once (using
// memcpy)
//

int *grow_buffer(int *array, int length, float growth_multiplier) {
  int new_buffer_size = (int)(length * growth_multiplier);
  int *arr = calloc(new_buffer_size, sizeof(int));
  memcpy(arr, array, sizeof(int) * length);
  return arr;
}

ArrayList *array_list_new(int *array, int length) {
  ArrayList *arraylist = malloc(sizeof(ArrayList));
  // arraylist->array = array;
  arraylist->length = length;
  int *new_array = grow_buffer(array, length, 1.5);
  arraylist->buffer = (int)(length * 1.5);
  arraylist->array = new_array;
  return arraylist;
}

void print_array_list(ArrayList *array_list) {
  for (int i = 0; i < array_list->length; i++) {
    printf("%d\n", array_list->array[i]);
  }
}


void print_array(int *array, int length) {
  for (int i = 0; i < length; i++) {
    printf("%d\n", array[i]);
  }
}

void push(ArrayList *array_list, int val) {
  int length = array_list->length;
  if (length == array_list->buffer) {
    array_list->array = grow_buffer(array_list->array, length, 2.0);
    array_list->buffer = length * 2;
  }
  array_list->array[length] = val;
  array_list->length++;
}

int pop(ArrayList *array_list) {
  int length = array_list->length;
  if (length == 0) {
    return -1;
  }
  array_list->length--;
  return array_list->array[length - 1];
}

// Queue operations
void enqueue(ArrayList *array_list, int val) { 
  push(array_list, val); 
}

int deque(ArrayList *array_list) {
  int length = array_list->length;
  if (length == 0) { return -1; }
  int val = array_list->array[0];
  int *array = array_list->array;
  memcpy(array, array + 1, (length - 1) * sizeof(int));
  array_list->length--;
  return val;
}

int main(int argc, char **argv) {
  // int array[15] = {4,6,8, 12, 14, 15, 16, 17, 25, 27, 35, 46, 52, 55, 62};
  int array[15] = {45, 23, 62,  58, 38, 8543, 734, 85,
                   34, 54, 856, 27, 55, 9375, 845};
  int length = sizeof(array) / sizeof(int);
  int arr[4] = {45, 23, 62, 58};
  // int arr2[8] = {0,0,0,0,0,0,0,0};
  ArrayList *array_list = array_list_new(arr, 4);
  enqueue(array_list, 7);
  enqueue(array_list, 93);
  enqueue(array_list, 107);
  int c = deque(array_list);
  int d = deque(array_list);
  int e = deque(array_list);
  printf("%d %d %d\n", c, d, e);
  print_array_list(array_list);
  // for (int i = 0; i < 6; i++) {
  //   printf("%d\n", arraylist->array[i]);
  // }
}
