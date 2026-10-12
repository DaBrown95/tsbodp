#include "display_text_fields.h"

void display_text_copy_field_zero(const char *source)
{
    unsigned char *destination = g_display_text_fields[0];
    while (*source) {
        *destination++ = *source++;
    }
    *destination = 0;
}
