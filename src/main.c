#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "array_list.h"


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
  return 0;
}
