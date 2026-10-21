#include "display_text_fields.h"

unsigned int display_text_copy_expanded(const unsigned char *source, char *destination)
{
    unsigned int count = 0;
    while (*source) {
        if (*source == '@') {
            ++source;
            display_text_copy_string(destination, (void *)display_text_substitution_field(*source));
            count += display_text_string_length((void *)display_text_substitution_field(*source));
            destination += display_text_string_length((void *)display_text_substitution_field(*source));
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
