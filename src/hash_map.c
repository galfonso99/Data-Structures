#include "hash_map.h"
#include <stdint.h>
#include <stdlib.h>
#include "fn_hash.h"
#include "stb_ds.h"

hashmap* create_hashmap(int capacity) {
    hashmap *map = malloc(sizeof(hashmap));
    // map->keys = calloc(capacity, sizeof(int));
    // map->values = calloc(capacity, sizeof(int));
    map->capacity = capacity;
    map->count = 0;
    map->data = (kv_pair ***) malloc(sizeof(kv_pair) * capacity);
    for (int i = 0; i < capacity; i++) {
        // adj_list[i] = (graph_edge *) malloc(sizeof(graph_edge) * length);
        // int length = edges_nr[i];
        map->data[i] = malloc(sizeof(kv_pair));
        map->data[i] = NULL;
        // for (int j = 0; j < length; j++) {
        //     /* adj_list[i][j] = list_of_edges[count]; */
        //     arrput(adj_list[i], list_of_edges[count]);
        //     count++;
        // }
    }
    return map;
}

kv_pair* create_pair(int index, int value) {
    kv_pair * pair = malloc(sizeof(kv_pair));
    pair->key = index;
    pair->value = value;
    return pair;
}

// uint32_t hash_function (uint32_t x) {
//     x = ((x >> 16) ^ x) * 0x45d9f3b;
//     x = ((x >> 16) ^ x) * 0x45d9f3b;
//     x = (x >> 16) ^ x;
//     return x;
// }

// int hash_function(int key, int capacity) {
//     return key % capacity;
// }

// int find_value (hashmap * map, int index) {
// }

void print_hashmap (hashmap * map) {
    for (int i = 0; i < map->capacity; i++) {
        kv_pair ** bucket = map->data[i];
        if (!bucket) {
            printf("The bucket was NULL\n");
            continue;
        }
        for (int j = 0; j < arrlen(bucket); j++) {
            kv_pair * pair = bucket[j];
            printf("Key: {%d}: Value: {%d} ", pair->key, pair->value);
        }
        printf("\n");
    }
}

void hashmap_set(hashmap *map, int key, int value) {
    // Handle the case where load ratio would exceed 0.7 so you have to rehash everything
    int hash = hashing_midsquare(key);
    int index = hash % map->capacity;
    kv_pair ** bucket = map->data[index];

    kv_pair * pair = create_pair(key, value);
    arrput(map->data[index], pair);
    // printf("%d\n", bucket[0]->value);
    // map->keys[index] = key;
    // map->values[index] = value;
    map->count++;
}
//
int hashmap_get(hashmap *map, int key) {
    int hash = hashing_midsquare(key);
    int index = hash % map->capacity;
    int value = -1;
    kv_pair ** bucket = map->data[index];
    for (int i = 0; i < arrlen(bucket); i++) {
        if (bucket[i]->key == key) {
            return bucket[i]->value;
        }
    }
    return value;
}
//
// void hashmap_delete (hashmap *map, int key) {
//     int index = hash_function(key, map->capacity);
//     map->keys[index] = -1;
//     map->values[index] = -1;
// }
