#include "display_text_runtime.h"

void *display_text_move_bytes(void *destination, const void *source,
                              unsigned int bytes)
{
    char *out = destination;
    const char *in = source;

    if ((unsigned int)in < (unsigned int)out &&
        (unsigned int)out < (unsigned int)in + bytes) {
        in += bytes;
        out += bytes;
        while (bytes--)
            *--out = *--in;
    } else {
        if (bytes > 15 && !(((unsigned int)in | (unsigned int)out) & 3)) {
            unsigned int *words_out = (unsigned int *)out;
            const unsigned int *words_in = (const unsigned int *)in;

            while (bytes > 15) {
                *words_out++ = *words_in++;
                *words_out++ = *words_in++;
                *words_out++ = *words_in++;
                *words_out++ = *words_in++;
                bytes -= 16;
            }
            while (bytes > 3) {
                *words_out++ = *words_in++;
                bytes -= 4;
            }
            out = (char *)words_out;
            in = (const char *)words_in;
        }
        while (bytes--)
            *out++ = *in++;
    }
    return destination;
}
