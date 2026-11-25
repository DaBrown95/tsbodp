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
#if TSBO_REVISION == 0
            if (*cursor == ' ') split = cursor;
            if (*(volatile const unsigned char *)cursor > 0xef) {
                ++cursor;
                font = g_display_fonts[1];
            } else font = g_display_fonts[0];
            width += display_text_glyph_width(font, *cursor);
#else
            /* Revision 1 also breaks at character F0 00 and measures
             * two-byte characters whole. */
            unsigned short code;
            if (*cursor == ' ' || (*cursor == 0xf0 && cursor[1] == 0)) split = cursor;
            code = *cursor;
            if (code > 0xef) {
                code = (code << 8) | *++cursor;
                font = g_display_fonts[1];
            } else font = g_display_fonts[0];
            width += display_text_glyph_width(font, code);
#endif
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
#if TSBO_REVISION == 0
        if (destination[-1] == '@') *destination++ = *cursor++;
#else
        /* Revision 1 ignores an '@' trail byte of a two-byte character. */
        if (destination[-1] == '@' && (unsigned char)destination[-2] <= 0xef)
            *destination++ = *cursor++;
#endif
        *destination = 0;
        *text = (const char *)cursor;
        tile = display_text_draw_line(tile, x, y, line, style);
        if (**text == '\n') ++*text;
        while (**text == ' ') ++*text;
    }
    return tile;
}
