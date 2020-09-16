#ifndef _DES_H_
#define _DES_H_

#include "cryper.h"
#include <stdint.h>

uint64_t cipher_block(uint64_t block, sub_keys_t keys);

#endif
