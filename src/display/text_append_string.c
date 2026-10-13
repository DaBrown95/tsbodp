#include "display_text_runtime.h"
#include "display_word_scan.h"

char *display_text_append_string(char *destination, const char *source)
{
    char *cursor = destination;
    const char *in = source;
    char *start = cursor;

    if (!((unsigned int)start & 3)) {
        const unsigned int *words = (const unsigned int *)cursor;

        while (!DISPLAY_WORD_HAS_ZERO(*words))
            ++words;
        cursor = (char *)words;
    }
    while (*cursor)
        ++cursor;
    display_text_copy_string(cursor, in);
    return start;
}
