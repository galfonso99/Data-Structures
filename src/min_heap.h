#ifndef MIN_HEAP_H
#define MIN_HEAP_H

#define STB_DS_IMPLEMENTATION
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "stb_ds.h"

typedef struct {
    int length;
    int * data;
} min_heap;

min_heap * min_heap_from_arr (int * arr, int length) {
    min_heap * heap = (min_heap*) malloc(sizeof(min_heap));
    heap->length = length;
    heap->data = NULL;
    for (int i = 0; i < length; i++) {
        arrput(heap->data, arr[i]);
    }
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
    printf("\n");

}

int parent(int child_idx) {
    return (child_idx - 1) / 2;
}

int left_child (int parent_idx) {
    return (parent_idx * 2) + 1;
}

int right_child(int parent_idx) {
    return (parent_idx * 2) + 2;
}

int min (int a, int b) {
    return a <= b ? a : b;
}

void swap (min_heap * heap, int child_idx, int parent_idx) {
    int * arr = heap->data;
    int tmp = arr[child_idx];
    arr[child_idx] = arr[parent_idx];
    arr[parent_idx] = tmp;
}

bool heapify_up (min_heap * heap, int idx) {
    int * arr = heap->data;
    int value = arr[idx];
    int parent_idx = parent(idx);
    while (parent_idx >= 0 && arr[parent_idx] > value) {
        swap(heap, idx, parent_idx);
        idx = parent_idx;
        parent_idx = parent(parent_idx);
    }
    return true;
}

bool heapify_down (min_heap * heap, int idx) {
    int * arr = heap->data;
    int l_idx = left_child(idx);
    int r_idx = right_child(idx);
    while (r_idx < heap->length && (arr[l_idx] < arr[idx] || arr[r_idx] < arr[idx])) {
        int min_idx = l_idx;
        if (arr[r_idx] < arr[l_idx]) {
            min_idx = r_idx;
        }
        swap(heap, idx, min_idx);
        idx = min_idx;
        l_idx = left_child(min_idx);
        r_idx = right_child(min_idx);
    }
    if (l_idx < heap->length && arr[l_idx] < arr[idx]) {
        swap(heap, idx, l_idx);
    }
    return true;
}

bool insert(min_heap * heap, int value) {
    // Insert the value into the end of the queue
    // Heapify up from that spot until parent is smaller or there is no more parents
    arrput(heap->data, value);
    heap->length++;
    bool success = heapify_up(heap, heap->length - 1);
    return success;
}

int pop(min_heap * heap) {
    if (heap->length == 0) return -1;
    // Swap first value with last value
    swap(heap, heap->length-1, 0);
    int value = arrpop(heap->data);
    heap->length--;
    heapify_down(heap, 0);
    return value;
}

void min_heap_driver () {
    /* int arr[13] = {12, 54, 15, 61, 77, 33, 34, 78, 80, 91, 100, 55, 77}; */
    int arr[3] = {12, 54, 15};
    int length = sizeof(arr) / sizeof(int);
    min_heap * heap = min_heap_from_arr((int *) &arr, length);
    print_heap(heap);
    printf("\n");
    /* int value = pop(heap); */
    printf("%d\n", pop(heap));
    print_heap(heap);
    printf("%d\n", pop(heap));
    print_heap(heap);
    printf("%d\n", pop(heap));
    print_heap(heap);
    printf("%d\n", pop(heap));
    print_heap(heap);
    printf("%d\n", pop(heap));
}

#endif
