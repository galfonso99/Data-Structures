#ifndef GENERIC_MAP_EXAMPLE_FNV1A_H
#define GENERIC_MAP_EXAMPLE_FNV1A_H

#include <stdint.h>
#define FNV_PRIME_32 0x01000193
#define FNV_OFFSET_32 0x811c9dc5

uint32_t fnv32(uint32_t x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
    /* uint32_t hash = FNV_OFFSET_32; */
    /* hash = (num ^ hash) * FNV_PRIME_32; */
    /* return hash; */
}

#endif
