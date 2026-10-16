#include "heap.h"

void *heap_move(void *memory, const void *source, unsigned int bytes)
{
    if ((unsigned int)source + bytes < (unsigned int)memory ||
        (unsigned int)source > (unsigned int)memory) {
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
    } else {
        const unsigned char *src = source;
        unsigned char *destination = memory;
        if (((unsigned int)memory & 3) || ((unsigned int)source & 3)) {
            int i;
            for (i = bytes - 1; i >= 0; --i)
                destination[i] = src[i];
        } else {
            int i;
            unsigned int trailing = bytes & 3;
            unsigned int words;
            unsigned int remaining;
            int word_index;
            const unsigned int *word_src;
            unsigned int *word_dst;
            i = bytes - 1;
            remaining = trailing--;
            words = bytes >> 2;
            if (remaining > 0) {
                do {
                    destination[i] = src[i];
                    --i;
                } while (trailing-- > 0);
            }
            /* Preserve the original exhausted remainder as a byte offset. */
            word_src = (const unsigned int *)((const unsigned char *)source + trailing);
            word_dst = (unsigned int *)((unsigned char *)memory + trailing);
            for (word_index = words - 1; word_index >= 0; --word_index)
                word_dst[word_index] = word_src[word_index];
        }
    }
    return memory;
}
