// #include "d_string.h"
// #include "my_array.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void bubble_sort (int* array, int length) {
  for (int j = 0; j < length - 1; j++) {
    for (int i = 0; i < length - j - 1; i++) {
      if (array[i] > array[i+1]) {
        array[i] ^= array[i+1];
        array[i+1] ^= array[i];
        array[i] ^= array[i+1];
      }
    }
  }
}

int main(int argc, char **argv) {
  // int array[15] = {4,6,8, 12, 14, 15, 16, 17, 25, 27, 35, 46, 52, 55, 62};
  int array[15] = {45,23,62,58,38,8543,734,85,34,54,856,27,55,9375,845};
  int length = sizeof(array) / sizeof(int);
  bubble_sort(array, length);
  for (int i = 0; i < length; i++) {
    printf("%d\n", array[i]);
  }
  // printf("%d\n", index);
}

