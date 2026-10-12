#include "heap.h"

void *heap_copy(void *memory, const void *source, unsigned int bytes)
{
    const unsigned char *src = source;
    unsigned char *destination = memory;
    unsigned int i;
    if (((unsigned int)memory & 3) || ((unsigned int)source & 3)) {
        for (i = 0; i < bytes; ++i) destination[i] = src[i];
    } else {
        unsigned int words = bytes >> 2;
        unsigned int trailing;
        i = 0;
        if (i < words) {
            const unsigned int *word_src = source;
            unsigned int *word_dst = memory;
            do {
                *word_dst++ = *word_src++;
                ++i;
            } while (i < words);
        }
        trailing = bytes & 3;
        i = bytes - trailing;
        while (trailing-- > 0) {
            destination[i] = src[i];
            ++i;
        }
    }
    return memory;
}
