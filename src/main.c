#define STB_DS_IMPLEMENTATION
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// #include "binary_tree.h"
#include "binary_search_tree.h"

int main (int argc, char **argv) {
    // int arr[13] = {12, 54, 15, 61, 77, 33, 34, 78, 80, 91, 100, 55, 77};
    int arr[7] = {7, 4, 12, 2, 5, 9, 15};
    int length = sizeof(arr) / sizeof(int);
    binary_search_tree_driver();
}

// for (int i = 0; i < length; i++) {
//     printf("%d\n", arr[i]);
// }
