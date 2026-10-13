#include "display_text_runtime.h"
#include "display_word_scan.h"

unsigned int display_text_string_length(const char *input)
{
    const char *cursor = input;
    const char *text = cursor;

    if (!((unsigned int)cursor & 3)) {
        const unsigned int *words = (const unsigned int *)cursor;

        while (!DISPLAY_WORD_HAS_ZERO(*words))
            ++words;
        cursor = (const char *)words;
    }
    while (*cursor)
        ++cursor;
    return cursor - text;
}
asm(".align 2, 0");
