#include "utils.h"

uint64_t permute(uint64_t input, const uint8_t *table, size_t len)
{
    uint64_t permuted = 0;
    for (int i = 0; i < len; i++) {
        if (input & (1 << table[i])) {
            permuted |= (1 << i);
        }
    }
    return permuted;
}
