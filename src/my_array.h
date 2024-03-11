#ifndef MY_ARRAY_H
#define MY_ARRAY_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  unsigned long size;
  int *start;
} Array;

Array * my_array_new(const int size);
int my_array_get_index(Array *array, unsigned int index);
void my_array_set_index(Array *mutArray, unsigned int index, int value);
int my_array_get_len(Array *array);
void my_array_free(Array *array);

#endif
