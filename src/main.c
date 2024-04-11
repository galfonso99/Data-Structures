#define STB_DS_IMPLEMENTATION
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// #include "binary_tree.h"
#include "stb_ds.h"

typedef struct {
    int length;
    int * data;
} min_heap;

min_heap * min_heap_from_arr (int * arr, int length) {
    min_heap * heap = malloc(sizeof(min_heap));
    heap->length = length;
    heap->data = NULL;
    for (int i = 0; i < length; i++) {
        arrput(heap->data, arr[i]);
    }
    // memcpy(heap->data, arr, sizeof(int) * length);
    return heap;
}

void print_heap (min_heap * heap) {
    int j = 0;
    int h = 0;
    for (int i = 0; i < heap->length; i++) {
        printf("%d, ", heap->data[i]);
        if (i == j) {
            printf("\n");
            j += 1 << (h + 1);
            h++;
        }
    }
}

int parent(int child_idx) {
    return (child_idx - 1) / 2;
}

int left_child(int parent_idx) {
    return (parent_idx * 2) + 1;
}

int right_child(int parent_idx) {
    return (parent_idx * 2) + 2;
}

void swap (min_heap * heap, int child_idx, int parent_idx) {
    int * arr = heap->data;
    int tmp = arr[child_idx];
    arr[child_idx] = arr[parent_idx];
    arr[parent_idx] = tmp;
}

bool heapify_up (min_heap * heap, int value, int idx) {
    int * arr = heap->data;
    int parent_idx = parent(idx);
    while (parent_idx >= 0 && arr[parent_idx] > value) {
        swap(heap, idx, parent_idx);
        idx = parent_idx;
        parent_idx = parent(parent_idx);
    }
    return true;
}

bool insert(min_heap * heap, int value) {
    // Insert the value into the end of the queue
    // Heapify up from that spot until parent is smaller or there is no more parents
    // int * arr = heap->data;
    arrput(heap->data, value);
    // for (int i = 0; i < 8; i++) {
    //     printf("%d\n", arr[i]);
    // }
    heap->length++;
    bool success = heapify_up(heap, value, heap->length - 1);
    return success;
}

int pop(min_heap * heap) {
    return -1;
}
// Maybe implement updating using a hashmap and bubble up or bubble down
int main (int argc, char **argv) {
    int arr[7] = {12, 34, 54, 45, 51, 61, 77};
    int length = sizeof(arr) / sizeof(int);
    min_heap * heap = min_heap_from_arr((int *) &arr, length);
    
    insert(heap, 33);
    // for (int i = 0; i < heap->length; i++) {
    //     printf("%d\n", heap->data[i]);
    // }
    insert(heap, 49);
    insert(heap, 15);
    print_heap(heap);
    // for (int i = 0; i < heap->length; i++) {
    //     printf("%d\n", heap->data[i]);
    // }
    // for (int i = 0; i < length; i++) {
    //     printf("%d\n", arr[i]);
    // }
    // binary_tree_driver();
}


// pop()
