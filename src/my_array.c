#include <stdio.h>
#include <stdlib.h>
#include "my_array.h" 


Array * my_array_new(const int size) {
  Array *newArray = malloc(sizeof(Array));
  newArray->start = malloc(sizeof(int) * size);
  newArray->size = size;
  return newArray;
}

int my_array_get_index(Array *array, unsigned int index) {
  if (index >= array->size) {
    printf("ERROR: Out of bounds access to array");
    exit(EXIT_FAILURE);
  }
  int value = *(array->start + index);
  return value;
}

void my_array_set_index(Array *mutArray, unsigned int index, int value) {
  if (index >= mutArray->size)
    return;
  int *location = mutArray->start + index;
  *location = value;
}

int my_array_get_len(Array *array) { return array->size; }

void my_array_free(Array *array) {
  free(array->start);
  free(array);
}

int run_my_array() {
  Array *newArray = my_array_new(10);
  int *buffer = newArray->start;
  for (int i = 0; i < 10; i++) {
    my_array_set_index(newArray, i, i * 2);
  };
  for (int j = 0; j < 10; j++) {
    int val = my_array_get_index(newArray, j);
    printf("%d\n", val);
  };
  printf("Size: %d\n", my_array_get_len(newArray));

  printf("Val: %d\n", buffer[3]);
  my_array_free(newArray);
  return 0;
}
