#include "display_text_fields.h"
#include "display_text_fields_inline.h"

void display_text_copy_field_two(const char *source)
{
    unsigned char *destination = display_text_field_address((void *)g_display_text_fields, 2);
    while (*source) {
        *destination++ = *source++;
    }
    *destination = 0;
}
