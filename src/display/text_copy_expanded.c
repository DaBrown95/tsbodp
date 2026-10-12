#include "display_text_fields.h"

unsigned int display_text_copy_expanded(const unsigned char *source, char *destination)
{
    unsigned int count = 0;
    while (*source) {
        if (*source == '@') {
            ++source;
            display_text_copy_string(destination, (void *)g_display_text_substitutions[*source]);
            count += display_text_string_length((void *)g_display_text_substitutions[*source]);
            destination += display_text_string_length((void *)g_display_text_substitutions[*source]);
            ++source;
        } else {
            *destination = *source;
            ++destination;
            ++source;
            ++count;
        }
    }
    *destination = 0;
    return count;
}

__asm__(".align 2, 0");
