/**
 * Tomado de 
 * https://github.com/jivanpal/drat/blob/main/include/drat/func/cksum.h
*/

#include <stdint.h>
#include <stdbool.h>

uint64_t fletcher_cksum(uint32_t* block, bool compute);
uint64_t compute_block_cksum(uint32_t* block);
bool is_cksum_valid(uint32_t* block, uint32_t block_size);
