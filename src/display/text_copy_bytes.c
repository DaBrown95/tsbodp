#include "display_text_runtime.h"

void *display_text_copy_bytes(void *destination, const void *source,
                              unsigned int bytes)
{
    char *out = destination;
    const char *in = source;

    if (bytes > 15 && !(((unsigned int)in | (unsigned int)out) & 3)) {
        unsigned int *words_out = (unsigned int *)out;
        /* Only the aligned source cursor uses this compiler allocation hint. */
        register const unsigned int *words_in asm("r3") = (const unsigned int *)in;

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
    return destination;
}
asm(".align 2, 0");
