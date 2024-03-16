#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "array_list.h"

// Implement RingBuffer aka ArrayBuffer
typedef struct {
    int *array;
    size_t length;
    size_t buffer;
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
    free(array);
    ring_buffer->array = new_array;
    ring_buffer->head_idx = length / 2;
    ring_buffer->tail_idx = ring_buffer->head_idx + length - 1;
}

RingBuffer *ring_buffer_new(int *array, int length) {
    RingBuffer *ring_buffer = malloc(sizeof(RingBuffer));
    ring_buffer->length = length;
    ring_buffer->buffer = length;
    ring_buffer->head_idx = 0;
    ring_buffer->tail_idx = length - 1;
    // ring_buffer->array = array;
    int *new_array = calloc(ring_buffer->buffer, sizeof(int));
    memcpy(new_array, array, length * sizeof(int));
    ring_buffer->array = new_array;
    double_array_size(ring_buffer, length);
    return ring_buffer;
}

void ring_buffer_free(RingBuffer *ring_buffer) {
    free(ring_buffer->array);
    free(ring_buffer);
}

int get (RingBuffer *ring_buffer, int index) {
    if (index >= ring_buffer->length) {
        return -1;
    }
    int adjusted_index = (ring_buffer->head_idx + index) % (ring_buffer->buffer);
        // printf("Index: %d\n", adjusted_index);
    return ring_buffer->array[adjusted_index];
}

void push (RingBuffer *ring_buffer, int val) {
    if (ring_buffer->length == ring_buffer->buffer) {
        double_array_size(ring_buffer, ring_buffer->length);
    }
    int new_tail_idx = (ring_buffer->tail_idx + 1) % (ring_buffer->buffer);
    ring_buffer->array[new_tail_idx] = val;
    ring_buffer->tail_idx = new_tail_idx;
    ring_buffer->length++;
}

int pop (RingBuffer *ring_buffer) {
    if (ring_buffer->length == 0) {
        return -31415;
    }
    int new_tail_idx = ring_buffer->tail_idx-1;
    if (new_tail_idx == - 1) {new_tail_idx = ring_buffer->buffer - 1;}
    int val = ring_buffer->array[ring_buffer->tail_idx];
    ring_buffer->tail_idx = new_tail_idx;
    ring_buffer->length--;
    return val;
}

void enqueue (RingBuffer *ring_buffer, int val) {
    if (ring_buffer->length == ring_buffer->buffer) {
        double_array_size(ring_buffer, ring_buffer->length);
    }
    int new_head_idx = ring_buffer->head_idx-1;
    if (new_head_idx == -1) {new_head_idx = ring_buffer->buffer - 1;}
    ring_buffer->array[new_head_idx] = val;
    ring_buffer->head_idx = new_head_idx;
    ring_buffer->length++;
}

int deque (RingBuffer *ring_buffer) {
    if (ring_buffer->length == 0) {
        return -31415;
    }
    int new_head_idx = (ring_buffer->head_idx + 1) % (ring_buffer->buffer);
    int val = ring_buffer->array[ring_buffer->head_idx];
    ring_buffer->head_idx = new_head_idx;
    ring_buffer->length--;
    return val;
}

//Implement append where 2 buffers are joined together
RingBuffer * append (RingBuffer *rb1, RingBuffer *rb2) {
    int new_length = rb1->length + rb2->length;
    RingBuffer *new_ring_buffer = malloc(sizeof(RingBuffer));
    int *new_array = calloc(new_length * 2, sizeof(int));
    int *arr1 = rb1->array, *arr2 = rb2->array;
    int rb1_start_to_tail = rb1->tail_idx + 1;
    int rb1_head_to_end = rb1->tail_idx - rb1->head_idx + 1;
    int rb2_start_to_tail = rb2->tail_idx + 1;
    int rb2_head_to_end = rb2->tail_idx - rb2->head_idx + 1;
    if (rb1->head_idx > rb1->tail_idx) {
        rb1_head_to_end = rb1->buffer - rb1->head_idx;
        memcpy(new_array + rb1_head_to_end, arr1, rb1_start_to_tail * sizeof(int));
    }
    if (rb2->head_idx > rb2->tail_idx) {
        rb2_head_to_end = rb2->buffer - rb2->head_idx;
        memcpy(new_array + rb1->length + rb2_head_to_end, arr2, rb2_start_to_tail * sizeof(int));
    }
    memcpy(new_array, arr1 + rb1->head_idx, rb1_head_to_end * sizeof(int));
    memcpy(new_array + rb1->length, arr2 + rb2->head_idx, rb2_head_to_end * sizeof(int));
    new_ring_buffer->array = new_array;
    new_ring_buffer->length = new_length;
    new_ring_buffer->buffer = new_length * 2;
    new_ring_buffer->head_idx = 0;
    new_ring_buffer->tail_idx = new_length;
    return new_ring_buffer;
}

int main(int argc, char **argv) {
    // int array[15] = {4,6,8, 12, 14, 15, 16, 17, 25, 27, 35, 46, 52, 55, 62};
    int array[15] = {45, 23, 62,  58, 38, 8543, 734, 85,
                   34, 54, 856, 27, 55, 9375, 845};
    // int length = sizeof(array) / sizeof(int);
    int arr[5] = {45, 23, 62, 58, 67};
    int arr2[7] = {78, 36, 654, 23, 53, 667, 6643};
    // int arr2[8] = {45, 23, 62, 58, 556, 67, 23, 65};
    int len1 = sizeof(arr) / sizeof(int);
    int len2 = sizeof(arr2) / sizeof(int);
    RingBuffer *ring_buffer = ring_buffer_new(arr, len1);
    RingBuffer *ring_buffer_2 = ring_buffer_new(arr2, len2);
    // printf("%lu\n", ring_buffer->tail_idx);
    push(ring_buffer, -346675);
    push(ring_buffer, -897332);
    push(ring_buffer, -28849);
    push(ring_buffer, -64747);
    push(ring_buffer_2, -346675);
    push(ring_buffer_2, -897332);
    push(ring_buffer_2, -28849);
    push(ring_buffer_2, -97379);
    push(ring_buffer_2, -64747);
    // for (int i = 0; i < ring_buffer->buffer; i++) {
    //     printf("%d\n", ring_buffer->array[i]);
    // }
    // printf("\n");
    // for (int i = 0; i < ring_buffer->buffer; i++) {
    //     printf("%d\n", ring_buffer->array[i]);
    // }
    // printf("\n");
    // printf("%lu\n", ring_buffer->head_idx);
    // printf("%d: %d: %d: %d\n", a,b,c,d);
    for (int i = 0; i < ring_buffer->buffer; i++) {
        printf("%d\n", ring_buffer->array[i]);
    }
    RingBuffer *ring_buffer_3 = append(ring_buffer, ring_buffer_2);
    // printf("%lu\n", ring_buffer_3->length);

    for (int i = 0; i < ring_buffer_3->buffer; i++) {
        // printf("%d\n", get(ring_buffer_3, i));
        printf("%d\n", ring_buffer_3->array[i]);
    }
    printf("\n");
    for (int i = 0; i < ring_buffer_3->length; i++) {
        printf("%d\n", get(ring_buffer_3, i));
    }
    printf("%lu\n", ring_buffer_3->length);
    ring_buffer_free(ring_buffer);
    ring_buffer_free(ring_buffer_2);
    ring_buffer_free(ring_buffer_3);
    return 0;
}
