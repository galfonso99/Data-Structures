#define STB_DS_IMPLEMENTATION

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "stb_ds.h"

// Implementing Quicksort
int partition (int *arr, int lo, int hi) {
    int pivot = arr[hi];
    int idx = lo - 1;   // Outside of the valid range

    for (int i = lo; i < hi; i++) {
        if (arr[i] <= pivot) {
            idx++;
            int curr = arr[i];
            arr[i] = arr[idx];
            arr[idx] = curr;
        }
    }
    idx++;
    arr[hi] = arr[idx];
    arr[idx] = pivot;

    return idx;
}

void qs (int *arr, int lo, int hi) {
    if (lo >= hi) {
        return;
    }

    int pivot_idx = partition(arr, lo, hi);

    qs(arr, lo, pivot_idx - 1);
    qs(arr, pivot_idx + 1, hi);
}

void quicksort (int *arr, int length) {
    qs(arr, 0, length-1);
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
