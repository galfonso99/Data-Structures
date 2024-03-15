#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "array_list.h"

// Implement RingBuffer aka ArrayBuffer
typedef struct {
    size_t length;
    size_t buffer;
    int *array;
    size_t head_idx;
    size_t tail_idx;
} RingBuffer;

void double_array_size (RingBuffer *ring_buffer, int length) {
    int new_buffer_size = length * 2;
    int *array = ring_buffer->array;
    int *new_array = calloc(new_buffer_size, sizeof(int));
    ring_buffer->buffer = new_buffer_size;
    int head_idx = ring_buffer->head_idx;
    int tail_idx = ring_buffer->tail_idx;
    int start_to_tail_length = tail_idx + 1;
    int head_to_end_length = length - head_idx;
    if (head_idx == 0) {
        memcpy(new_array + (length / 2), array, length * sizeof(int));
    } else {
        memcpy(new_array + (length / 2),
            array + head_idx,
            head_to_end_length * sizeof(int));
        memcpy(new_array + (length / 2) + head_to_end_length,
            array,
            start_to_tail_length * sizeof(int));
    }
    ring_buffer->array = new_array;
    ring_buffer->head_idx = length / 2;
    ring_buffer->tail_idx = new_buffer_size - 1 - length / 2;
}

RingBuffer *ring_buffer_new(int *array, int length) {
    RingBuffer *ring_buffer = malloc(sizeof(RingBuffer));
    ring_buffer->length = length;
    ring_buffer->buffer = length * 2;
    ring_buffer->head_idx = 0;
    ring_buffer->tail_idx = length - 1;
    ring_buffer->array = array;
    int *new_array = calloc(ring_buffer->buffer, sizeof(int));
    double_array_size(ring_buffer, length);
    return ring_buffer;
}

void push (RingBuffer *ring_buffer, int val) {
    if (ring_buffer->length == ring_buffer->buffer) {
        double_array_size(ring_buffer, ring_buffer->length);
        printf("We got there\n");
    }
    int new_tail_idx = (ring_buffer->tail_idx + 1) % (ring_buffer->buffer);
    ring_buffer->array[new_tail_idx] = val;
    ring_buffer->tail_idx = new_tail_idx;
    ring_buffer->length++;
}

int main(int argc, char **argv) {
    // int array[15] = {4,6,8, 12, 14, 15, 16, 17, 25, 27, 35, 46, 52, 55, 62};
    int array[15] = {45, 23, 62,  58, 38, 8543, 734, 85,
                   34, 54, 856, 27, 55, 9375, 845};
    // int length = sizeof(array) / sizeof(int);
    int arr[4] = {45, 23, 62, 58};
    int arr2[8] = {45, 23, 62, 58, 556, 67, 23, 65};
    int length = sizeof(arr) / sizeof(int);
    RingBuffer *ring_buffer = ring_buffer_new(arr, length);
    // double_array_size(ring_buffer, ring_buffer->buffer);
    // ring_buffer->array = arr2;
    // ring_buffer->length = 8;
    // ring_buffer->buffer = 8;
    // ring_buffer->head_idx = 0;
    // ring_buffer->tail_idx = ring_buffer->length-1;
    // double_array_size(ring_buffer, ring_buffer->buffer);
    push(ring_buffer, -346675);
    push(ring_buffer, -897332);
    push(ring_buffer, -28849);
    push(ring_buffer, -97379);
    for (int i = 0; i < ring_buffer->buffer; i++) {
        printf("%d\n", ring_buffer->array[i]);
    }
    push(ring_buffer, -1575543);
    for (int i = 0; i < 16; i++) {
        printf("%d\n", ring_buffer->array[i]);
    }
    return 0;
}
