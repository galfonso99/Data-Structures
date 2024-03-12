// #include "d_string.h"
// #include "my_array.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int two_crystal_balls(int* stories, int length, int breaking_point) {
  int jump = sqrt(length);
  int floor = -1;
  int i = jump;
  for (; i < length; i+=jump) {
    if (stories[i] >= breaking_point) {break;}
  }
  i -= jump;
  for (int j = 0; j <= jump; j++) {
    if (stories[i + j] >= breaking_point) {
      floor = i + j;
      break;
    }
  }
  return floor;
}

int main(int argc, char **argv) {
  int array[15] = {4,6,8, 12, 14, 15, 16, 17, 25, 27, 35, 46, 52, 55, 62};
  int length = sizeof(array) / sizeof(int);
  for (int j = 0; j < length; j++) {
    printf("%d\n", array[j]);
  };
  int index = two_crystal_balls(array, length, 12);
  printf("%d\n", index);
}

