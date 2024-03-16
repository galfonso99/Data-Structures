#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ring_buffer.h"

// Implement RingBuffer aka ArrayBuffer

int main(int argc, char **argv) {
    int arr[5] = {45, 23, 62, 58, 67};
    int arr2[7] = {78, 36, 654, 23, 53, 667, 6643};
    int len1 = sizeof(arr) / sizeof(int);
    int len2 = sizeof(arr2) / sizeof(int);
    // RingBuffer *ring_buffer = ring_buffer_new(arr, len1);
    // RingBuffer *ring_buffer_2 = ring_buffer_new(arr2, len2);
    // for (int i = 0; i < ring_buffer->buffer; i++) {
    //     printf("%d\n", ring_buffer->array[i]);
    // }
}
