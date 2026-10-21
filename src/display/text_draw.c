#include "display_text_draw.h"
#include "display_text_measure_inline.h"

unsigned int display_text_draw(unsigned int tile, int x, int y, int max_width,
                               const char **text, unsigned int style, unsigned int *limit)
{
    char line[96];
    const unsigned char *cursor = (const unsigned char *)*text;
    const unsigned char *split = 0, *hyphen = 0;
    int width = 0;
    while (*cursor && width <= max_width) {
        if (*cursor == '\n') {
            split = cursor;
            break;
        }
        if (*cursor == '@') {
            ++cursor;
            width += display_text_width_inline((const char *)display_text_substitution_field(*cursor));
        } else {
            const struct DisplayFont *font;
            if (*cursor == ' ') split = cursor;
            if (*(volatile const unsigned char *)cursor > 0xef) {
                ++cursor;
                font = g_display_fonts[1];
            } else font = g_display_fonts[0];
            width += display_text_glyph_width(font, *cursor);
            if (*cursor == '-' && width <= max_width) hyphen = cursor + 1;
        }
        ++cursor;
    }
    if (!*cursor && width <= max_width) split = cursor;
    if (!split) {
        if (!hyphen) return tile;
        split = hyphen;
    }
    {
        char *destination = line;
        cursor = (const unsigned char *)*text;
        while (cursor != split && *limit) {
            *destination++ = *cursor++;
            --*limit;
        }
        if (destination[-1] == '@') *destination++ = *cursor++;
        *destination = 0;
        *text = (const char *)cursor;
        tile = display_text_draw_line(tile, x, y, line, style);
        if (**text == '\n') ++*text;
        while (**text == ' ') ++*text;
    }
    return tile;
}
