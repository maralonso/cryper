#include "key.h"
#include "utils.h"

#define PERMUTED_1_LEN  56
#define PERMUTED_1_MASK 0x0FFFFFFF
#define PERMUTED_2_LEN  48
#define PERMUTED_2_MASK 0x0FFFFFFF

static const uint8_t PERMUTED_CHOISE_1[PERMUTED_1_LEN] = {
    57, 49, 41, 33, 25, 17, 9, 
    1, 58, 50, 42, 34, 26, 18, 
    10, 2, 59, 51, 43, 35, 27, 
    19, 11, 3, 60, 52, 44, 36,           
    63, 55, 47, 39, 31, 23, 15, 
    7, 62, 54, 46, 38, 30, 22, 
    14, 6, 61, 53, 45, 37, 29, 
    21, 13, 5, 28, 20, 12, 4 
};

static const uint8_t  PERMUTED_CHOISE_2[PERMUTED_2_LEN] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

void get_sub_keys(uint64_t key, actions_e action, sub_keys_t *keys)
{
   uint64_t cipher = permute(key, PERMUTED_CHOISE_1, PERMUTED_1_LEN); 

   uint32_t cipher_left = cipher & 0x0FFFFFFF;
   uint32_t cipher_right = (cipher >> 27) & 0x0FFFFFFF;

   for (int i = 0; i < 16; i++) {
        cipher_left = (cipher_left << 1) | ((cipher_left & 0x8000000) >> 27);
        cipher_right = (cipher_right << 1) | ((cipher_right & 0x8000000) >> 27);

        if ((i != 0) && (i != 1) & (i != 8) && (i != 15)) {
            cipher_left = (cipher_left << 1) | ((cipher_left & 0x8000000) >> 27);
            cipher_right = (cipher_right << 1) | ((cipher_right & 0x8000000) >> 27);
        }

        keys->key[i] = permuted(cipher_left | (cipher_right << 28), PERMUTED_CHOISE_2, PERMUTED_2_LEN); 
   }
}
