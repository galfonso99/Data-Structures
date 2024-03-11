#include "d_string.h"
#include "my_array.h"
#include <stdio.h>
#include <stdlib.h>

int linear_search(int *array, int length, int val) {
  for (int i = 0; i < length; i++) {
    if (array[i] == val) {
      return i;
    }
  }
  return -1;
  /* Linear search but without returning inside a loop
    int found_index = -1;
    int length = sizeof(array) / sizeof(int);
    for (int i = 0; i < length; i++) {
      if (array[i] == val) {
        found_index = i;
        break;
      }
    }
    return found_index;
  */
}

int binary_search(int *haystack, int length, int needle) {
  int start = 0, end = length - 1;
  int middle;
  int index = -1;
  while (start <= end) {
    middle = start + (end - start) / 2;
    if (haystack[middle] > needle) {
      end = middle - 1;
    } else if (haystack[middle] < needle) {
      start = middle + 1;
    } else {
      index = middle;
      break;
    }
  }
  return index;
}

int main(int argc, char **argv) {
  // run_my_array();
  int array[15] = {4,6,8, 12, 14, 15, 16, 17, 25, 27, 35, 46, 52, 55, 62};
  int length = sizeof(array) / sizeof(int);
  for (int j = 0; j < length; j++) {
    printf("%d\n", array[j]);
  };
  int index = binary_search(array, length, 15);
  printf("%d\n", index);
}

// void run_my_array() {
//   Array *newArray = my_array_new(10);
//   int *buffer = newArray->start;
//   for (int i = 0; i < 10; i++) {
//     my_array_set_index(newArray, i, i * 2);
//   };
//   for (int j = 0; j < 10; j++) {
//     int val = my_array_get_index(newArray, j);
//     printf("%d\n", val);
//   };
//   printf("Size: %d\n", my_array_get_len(newArray));
//   printf("Val: %d\n", buffer[3]);
//   my_array_free(newArray);
// }
