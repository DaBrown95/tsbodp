#include "display_text_runtime.h"

void *display_fill_bytes(void *destination, int value, unsigned int bytes)
{
    char *out = destination;

    if (bytes > 3 && !((unsigned int)out & 3)) {
        unsigned int *words = (unsigned int *)out;
        unsigned int repeated;

        value &= 255;
        repeated = (value << 8) | value;
        repeated |= repeated << 16;
        while (bytes > 15) {
            *words++ = repeated;
            *words++ = repeated;
            *words++ = repeated;
            *words++ = repeated;
            bytes -= 16;
        }
        while (bytes > 3) {
            *words++ = repeated;
            bytes -= 4;
        }
        out = (char *)words;
    }
    for (;;) {
        unsigned int previous = bytes--;
        if (!previous)
            break;
        *out++ = value;
    }
    return destination;
}
asm(".align 2, 0");
