#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *array;
    size_t length;
    size_t buffer;
    size_t head_idx;
    size_t tail_idx;
} RingBuffer;

void double_array_size (RingBuffer *ring_buffer, int length); 

RingBuffer *ring_buffer_new(int *array, int length); 

void ring_buffer_free(RingBuffer *ring_buffer); 

int get (RingBuffer *ring_buffer, int index); 

void push (RingBuffer *ring_buffer, int val); 

int pop (RingBuffer *ring_buffer); 

void enqueue (RingBuffer *ring_buffer, int val); 

int deque (RingBuffer *ring_buffer); 

RingBuffer * append (RingBuffer *rb1, RingBuffer *rb2); 

void ring_buffer_driver();
#endif
