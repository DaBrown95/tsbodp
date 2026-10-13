#include "display_text_runtime.h"
#include "display_word_scan.h"

char *display_text_copy_string(char *destination, const char *source)
{
    char *out = destination;
    const char *in = source;

    if (!(((unsigned int)in | (unsigned int)out) & 3)) {
        unsigned int *words_out = (unsigned int *)out;
        const unsigned int *words_in = (const unsigned int *)in;

        while (!DISPLAY_WORD_HAS_ZERO(*words_in))
            *words_out++ = *words_in++;
        out = (char *)words_out;
        in = (const char *)words_in;
    }
    while ((*out++ = *in++) != 0) {
    }
    return destination;
}
asm(".align 2, 0");
