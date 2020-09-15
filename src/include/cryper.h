#ifndef _CRYPER_H_
#define _CRYPER_H_

#include <stdint.h>

typedef enum {
    ENCRYPT=1,
    DECRYPT,
}actions_e;

#define SUB_KEYS_LEN    16

typedef struct {
    uint64_t key[SUB_KEYS_LEN];
} sub_keys_t;

#endif
