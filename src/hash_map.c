#include "hash_map.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "fn_hash.h"
#include "stb_ds.h"

hashmap* create_hashmap(int capacity) {
    hashmap *map = malloc(sizeof(hashmap));
    map->capacity = capacity;
    map->count = 0;
    map->data = (kv_pair ***) malloc(sizeof(kv_pair) * capacity);
    for (int i = 0; i < capacity; i++) {
        // map->data[i] = malloc(sizeof(kv_pair));
        map->data[i] = NULL;
    }
    return map;
}

kv_pair* create_pair(int index, int value) {
    kv_pair * pair = malloc(sizeof(kv_pair));
    pair->key = index;
    pair->value = value;
    return pair;
}

void print_hashmap (hashmap * map) {
    for (int i = 0; i < map->capacity; i++) {
        kv_pair ** bucket = map->data[i];
        if (arrlen(bucket) == 0) {
            printf("Index: %d Empty", i);
        }
        for (int j = 0; j < arrlen(bucket); j++) {
            kv_pair * pair = bucket[j];
            printf("Index: %d Key: {%d}: Value: {%d} \t\t", i, pair->key, pair->value);
        }
        printf("\n");
    }
}

void hashmap_rehash (hashmap * map, int new_capacity) {
    kv_pair ** pairs = NULL;
    map->count = 0;
    // Loop through the data array and collect all the kv_pairs into a 1D array while setting that bucket to NULL
    for (int i = 0; i < new_capacity; i++) {
        kv_pair ** bucket = map->data[i];
        for (int j = 0; j < arrlen(bucket); j++) {
            kv_pair * pair = bucket[j];
            arrput(pairs, pair);
        }
        map->data[i] = NULL;
    }
    // Loop through the new 1D array and for each value pair hash them with the new info and insert into the data array
    for (int i = 0; i < arrlen(pairs); i++) {
        kv_pair * pair = pairs[i];
        int key = pair->key;
        int hash = hashing_midsquare(key);
        int index = hash % new_capacity;
        arrput(map->data[index], pair);
        map->count++;
    }
    map->capacity = new_capacity;
    arrfree(pairs);
}

bool hashmap_has (hashmap * map, int key) {
    int hash = hashing_midsquare(key);
    int index = hash % map->capacity;
    kv_pair ** bucket = map->data[index];
    for (int i = 0; i < arrlen(bucket); i++) {
        if (bucket[i]->key == key) {
            return true;
        }
    }
    return false;
}

void hashmap_update (hashmap * map, int key, int value) {
    int hash = hashing_midsquare(key);
    int index = hash % map->capacity;
    kv_pair ** bucket = map->data[index];
    for (int i = 0; i < arrlen(bucket); i++) {
        if (bucket[i]->key == key) {
            bucket[i]->value = value;
            break;
        }
    }
}

void hashmap_set(hashmap *map, int key, int value) {
    // If Key already exists only update the value 
    if (hashmap_has(map, key)) {
        hashmap_update(map, key, value);
        return;
    }
    // Rehash hashmap with double capacity if the load factor exceeds 7 / 10
    int load_factor = map->count * 10 / map->capacity;
    if (load_factor >= 7) {
        hashmap_rehash(map, map->capacity * 2);
    }
    // Insert the value into the map if the key wasn't in the hashmap previously
    int hash = hashing_midsquare(key);
    int index = hash % map->capacity;
    kv_pair * pair = create_pair(key, value);
    arrput(map->data[index], pair);
    map->count++;
}
//
int hashmap_get(hashmap *map, int key) {
    int hash = hashing_midsquare(key);
    int index = hash % map->capacity;
    int value = -1;
    kv_pair ** bucket = map->data[index];
    // Length of bucket should rarely be bigger than 3 so we consider this constant time
    for (int i = 0; i < arrlen(bucket); i++) {
        if (bucket[i]->key == key) {
            return bucket[i]->value;
        }
    }
    return value;
}

void hashmap_delete (hashmap *map, int key) {
    int hash = hashing_midsquare(key);
    int index = hash % map->capacity;
    kv_pair ** bucket = map->data[index];
    for (int i = 0; i < arrlen(bucket); i++) {
        if (bucket[i]->key != key) continue;
        arrdel(bucket, i);
        break;
    }
    map->count--;
}

void hashmap_free (hashmap * map) {
    free(map->data);
    free(map);
}

void print_entry (int key, int value, void * usr_ptr) {
	printf("Entry \"%d\": %d\n", key, value);
}

void accumulate_entry (int key, int value, void * usr_ptr) {
    int * total = (int *) usr_ptr;
    *total = *total + value;
}

void hashmap_iterate (hashmap * map, callback_function func, void * usr_ptr) {
    for (int i = 0; i < map->capacity; i++) {
        kv_pair ** bucket = map->data[i];
        for (int j = 0; j < arrlen(bucket); j++) {
            kv_pair * pair = bucket[j];
            func (pair->key, pair->value, usr_ptr);
        }
    }
}

void hashmap_driver () {
    int capacity = 10;
    hashmap * map = create_hashmap(capacity);
    hashmap_set(map, 5, 25);
    hashmap_set(map, 634, 6356);
    hashmap_set(map, 69, 420);
    hashmap_set(map, 8, 64);
    hashmap_set(map, 55555, 777);
    print_hashmap(map);
    printf("Map count: %d\n", map->count);
    hashmap_set(map, 45, 678);
    hashmap_set(map, 33, 998);
    hashmap_set(map, 123, 546);
    hashmap_set(map, 125, 546);
    int x = hashmap_get(map, 5);
    // printf("%d\n", x);
    printf("\n");
    printf("\n");
    // hashmap_free(map);
    // hashmap_delete(map, 69);
    // hashmap_rehash(map, 15);
    hashmap_set(map, 55555, 444);
    hashmap_set(map, 42069, 69420);
    hashmap_delete(map, 5);
    print_hashmap(map);
    printf("Map count: %d\n", map->count);
    int acc = 0;
    hashmap_iterate(map, accumulate_entry, &acc);
    printf("Sum total: %d\n", acc);
}
