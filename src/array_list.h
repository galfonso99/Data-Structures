#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdlib.h>

typedef struct {
  size_t length;
  size_t buffer;
  int *array;
} ArrayList;


int *grow_array(int *array, int length, float growth_multiplier); 

ArrayList *array_list_new(int *array, int length); 

void print_array_list(ArrayList *array_list); 

void print_array(int *array, int length); 

void push(ArrayList *array_list, int val); 

int pop(ArrayList *array_list); 

// Queue operations
void enqueue(ArrayList *array_list, int val); 

int deque(ArrayList *array_list); 

#endif
