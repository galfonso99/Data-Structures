#define STB_DS_IMPLEMENTATION

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "stb_ds.h"

// Implementing Quicksort
void split (int *arr, int lo, int hi) {
    if (hi - lo < 1)  {
        return;
    }
    int pivot = arr[hi];
    int count = lo;
    // Skip until you find a value that is >= pivot
    while (arr[count] < pivot) {
        count++;
    }
    int swap_idx = count;
    // Swap every larger value with a smaller value until all the smaller values are at the front
    for (int i = count + 1; i < hi + 1; i++) {
        if (arr[i] < pivot) {
            int current = arr[i];
            arr[i] = arr[swap_idx];
            arr[swap_idx] = current;
            swap_idx++;
        }
    }
    // Place the pivot right after the last value that is lesser than it
    arr[hi] = arr[swap_idx];
    arr[swap_idx] = pivot;
    int pivot_idx = swap_idx;
    // Repeat at the left side and right side of the pivot
    split(arr, lo, pivot_idx - 1);
    split(arr, pivot_idx + 1, hi);
}

void quicksort (int *arr, int length) {
    split(arr, 0, length-1);
}

int main (int argc, char **argv) {
    int array[15] = {45, 23, 62,  58, 38, 8543, 734, 85,
                   34, 54, 856, 27, 55, 9375, 845};
    // int array[7] = {9, 3, 7, 4, 69, 420, 42};
    int length = sizeof(array) / sizeof(int);
    int arr[5] = {45, 23, 62, 58, 67};
    int arr2[7] = {78, 36, 654, 23, 53, 667, 6643};
    int len1 = sizeof(arr) / sizeof(int);
    int len2 = sizeof(arr2) / sizeof(int);  
    quicksort(array, length);
    for (int i = 0; i < length; i++) {
        printf("%d\n", array[i]);
    }
}

    // printf("%d %d %d\n", middle, lo, hi);
    // printf("Pivot: %d\n", pivot);
    // printf("swappable_idx: %d\n", swappable_idx);
    // printf("Low: %d\n", lo);
    // for (int i = lo; i < hi + 1; i++) {
    //     printf("%d\n", arr[i]);
    // }
    // printf("\n");
