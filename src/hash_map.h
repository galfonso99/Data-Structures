#ifndef HASH_MAP_H
#define HASH_MAP_H

/* #include "generic_map.h" */

#include <string.h>
#include <stdlib.h>

typedef struct {
    int *keys;
    int *values;
    int size;
    int count;
} hashmap;

hashmap* create_hash_map(int size);

int hash_function(int key, int size);

void hashmap_insert(hashmap *map, int key, int value);

int hashmap_get(hashmap *map, int key); 

void hashmap_delete (hashmap *map, int key);

#endif
