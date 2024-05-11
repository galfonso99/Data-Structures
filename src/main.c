#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include "hash_map.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"


// Mentally prepare for a lot of seg faults
// stuff left to do:
// Free the hashmap
// Resize when load factor over 0.7
// Delete a entry of the hashmap
// Iterate over the map given a func pointer
int main (int argc, char **argv) {
    // lru_driver();
    int capacity = 10;
    hashmap * map = create_hashmap(capacity);
    hashmap_set(map, 5, 25);
    hashmap_set(map, 634, 6356);
    hashmap_set(map, 69, 420);
    hashmap_set(map, 8, 64);
    hashmap_set(map, 55555, 777);
    int x = hashmap_get(map, 5);
    printf("%d\n", x);
    print_hashmap(map);

}
