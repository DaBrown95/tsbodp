#include "display_text_fields.h"

char *display_text_expand_resource(unsigned int id)
{
    unsigned int index = 0;
    char *text = (char *)display_scene_lookup_text(id);
    if (display_text_find_character(text, '@')) {
        while (text[index]) {
            if (text[index] == '@') {
                char *replacement;
                unsigned int length;
                char *tail, *destination;
                int next_index;
                ++index;
                replacement = (char *)display_text_substitution_field((unsigned char)text[index]);
                length = display_text_string_length(replacement);
                ++index;
                destination = text + (index + length - 2);
                tail = text + index;
                display_text_move_bytes(destination, tail, display_text_string_length(tail) + 1);
                display_text_copy_bytes(tail - 2, replacement, length);
                next_index = index - 2;
                index = next_index + length;
            } else ++index;
        }
    }
    return text;
}

__asm__(".align 2, 0");
