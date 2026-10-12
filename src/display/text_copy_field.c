#include "display_text_fields.h"

void display_text_copy_field(const char *source, unsigned int slot)
{
    unsigned char *destination = g_display_text_fields[slot];
    while (*source) {
        *destination++ = *source++;
    }
    *destination = 0;
}
