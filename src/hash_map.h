#ifndef HASH_MAP_H
#define HASH_MAP_H

/* #include "generic_map.h" */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} kv_pair;

typedef struct {
    /* int *keys; */
    /* int *values; */
    kv_pair *** data;
    int capacity;
    int count;
} hashmap;




hashmap* create_hashmap(int capacity);

void print_hashmap (hashmap * map);

uint32_t hash_function(uint32_t key);

void hashmap_set(hashmap *map, int key, int value);

int hashmap_get(hashmap *map, int key); 

void hashmap_delete (hashmap *map, int key);

#endif
