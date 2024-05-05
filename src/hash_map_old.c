#include <string.h>
#include "hash_map.h"
#include "fn_hash.h"

int compare_int (int a, int b) {
    return (a > b) - (a < b);
}

define_map_c(IIMap, uint32_t, uint32_t, fnv32, compare_int, -1)
