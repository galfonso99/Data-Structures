#include "hash_map.h"

hashmap* create_hash_map(int size) {
    hashmap *map = malloc(sizeof(hashmap));
    map->keys = calloc(size, sizeof(int));
    map->values = calloc(size, sizeof(int));
    map->size = size;
    map->count = 0;
    return map;
}

int hash_function(int key, int size) {
    return key % size;
}

void hashmap_set(hashmap *map, int key, int value) {
    int index = hash_function(key, map->size);
    map->keys[index] = key;
    map->values[index] = value;
    map->count++;
}

int hashmap_get(hashmap *map, int key) {
    int index = hash_function(key, map->size);
    if (map->keys[index] == key) {
        return map->values[index];
    }
    return -1; // Key not found
}

void hashmap_delete (hashmap *map, int key) {
    int index = hash_function(key, map->size);
    map->keys[index] = -1;
    map->values[index] = -1;
}
