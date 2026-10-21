#include "display_text_fields.h"
#include "display_text_fields_inline.h"

void display_text_copy_field_three_unrooted_1b480(const char *source)
{
    unsigned char *destination = display_text_field_address((void *)g_display_text_fields, 3);
    while (*source) {
        *destination++ = *source++;
    }
    *destination = 0;
}
