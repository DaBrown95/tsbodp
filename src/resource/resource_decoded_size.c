#include "resource_decode.h"
unsigned int resource_decoded_size(const void *source) {
 return *(const unsigned int *)source >> 8;
}
asm(".align 2, 0");
