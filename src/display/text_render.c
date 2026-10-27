#include "display_text_raster.h"

/* Render glyph columns through the shared tile-row buffer. */
unsigned int display_text_render(unsigned int input_tile, int x, int y,
                                const char *text)
{
    unsigned int storage[64];
    const unsigned char *cursor;
    const unsigned char *resume;
    unsigned int substituted;
    unsigned short *map;
    void *tiles;
    unsigned int palette;
    /* The live font stays in callee-saved R5 across the row providers. */
    register const struct DisplayFont *font asm("r5");
    const struct DisplayFont *alternate_font;
    const struct DisplayFont *default_font;
    unsigned char *buffer;
    unsigned int tile;
    unsigned int color;
    const unsigned char *next_cursor;
    int rows;

    tile = input_tile;
    color = 0;
    map = display_text_map_position(g_display_text_state.map, x, y);
    tiles = g_display_text_state.tiles;
    palette = g_display_text_state.palette_base;
    font = g_display_text_state.font;
    alternate_font = g_display_text_state.alternate_font;
    default_font = font;
    x &= 7;
    y &= 7;
    rows = (y + font->height + 7) >> 3;
    buffer = (unsigned char *)storage;
    if (g_display_text_state.fill == -1)
        display_text_read_rows((unsigned int *)buffer, rows, map, tiles);
    else
        display_text_fill_rows((unsigned int *)buffer, rows, g_display_text_state.fill);

    cursor = (const unsigned char *)text;
    resume = cursor;
    substituted = 0;
    while (*cursor || substituted) {
        unsigned int glyph;
        unsigned int leading;
        int index;
        const unsigned char *pixels;
        unsigned int bit;
        unsigned int width;
        if (substituted && !*cursor) {
            cursor = resume;
            substituted = 0;
            if (!*cursor) break;
        }
        if (!substituted && *cursor == '@') {
            ++cursor;
            resume = cursor;
            cursor = display_text_substitution_field(*cursor);
            ++resume;
            substituted = 1;
        }
        /* The leading byte and decoded byte are separate native observations. */
        leading = *(volatile const unsigned char *)cursor;
        if (leading > 0xef) {
            leading <<= 8;
            ++cursor;
            glyph = *cursor;
            glyph |= leading;
            font = alternate_font;
        } else {
            font = default_font;
            glyph = *cursor;
        }
        index = (int)glyph - font->first;
        /* Preserve the first-field reload on the bounds-check path. */
        if (index < 0 ||
            index > font->last - ((volatile const struct DisplayFont *)font)->first)
            index = 1;
        pixels = font->glyph_pixels + font->glyph_offsets[index];
        bit = 0;
        width = font->widths[index];
        for (;;) {
            unsigned int previous_width = width;
            unsigned int height;
            width = previous_width - 1;
            next_cursor = cursor + 1;
            if (previous_width == 0) break;
            if (g_display_text_state.wide_color == 1) {
                unsigned char *destination = (unsigned char *)storage + y * 8 + x;
                height = font->height;
                for (;;) {
                    unsigned int previous_height = height;
                    height = previous_height - 1;
                    if (previous_height == 0) break;
                    if (bit == 8) { bit = 0; ++pixels; }
                    glyph = (*pixels >> bit) & 3;
                    if (glyph) {
                        if (g_display_text_state.pixel_mode == 0) color = glyph;
                        else if (g_display_text_state.pixel_mode == 1) color = 0;
                        *destination = color + palette;
                    }
                    destination += 8;
                    bit += 2;
                }
            } else {
                unsigned char *destination = (unsigned char *)storage + (y * 8 + x) / 2;
                unsigned int odd;
                height = font->height;
                for (;;) {
                    unsigned int previous_height = height;
                    unsigned int value;
                    height = previous_height - 1;
                    if (previous_height == 0) break;
                    odd = x & 1;
                    if (bit == 8) { bit = 0; ++pixels; }
                    value = (*pixels >> bit) & 3;
                    if (value) {
                        if (g_display_text_state.pixel_mode == 0) color = value;
                        else if (g_display_text_state.pixel_mode == 1) color = 0;
                        if (!odd) {
                            unsigned int retained = *destination & 0xf0;
                            unsigned int sum = color + palette;
                            *destination = retained | sum;
                        } else {
                            unsigned int retained = *destination & 15;
                            unsigned int sum = color + palette;
                            *destination = retained | (sum << 4);
                        }
                    }
                    destination += 4;
                    bit += 2;
                }
            }
            ++x;
            if (x == 8) {
                x = 0;
                display_text_emit_rows((unsigned int *)buffer, rows, map, tiles, tile);
                tile += rows;
                ++map;
                if (g_display_text_state.fill == -1)
                    display_text_read_rows((unsigned int *)buffer, rows, map, tiles);
                else
                    display_text_fill_rows((unsigned int *)buffer, rows, g_display_text_state.fill);
            }
        }
        cursor = next_cursor;
    }
    if (x > 0) {
        display_text_emit_rows((unsigned int *)buffer, rows, map, tiles, tile);
        tile += rows;
    }
    g_display_text_state.dirty = 1;
    return tile;
}
