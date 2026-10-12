#include "display_text_raster.h"

void display_text_load_font(unsigned int group, unsigned int slot)
{
    const unsigned char *data = g_display_font_resources[group].data;
    struct DisplayFont *font = &g_display_font_banks[group][slot];
    font->first = *(const unsigned short *)data;
    font->last = *(const unsigned short *)(data + 2);
    font->height = data[4];
    font->line_advance = g_display_font_resources[group].line_advance;
    font->glyph_offsets = (const void *)(data + ((data[6] << 8) + data[7]));
    font->widths = data + ((data[10] << 8) + data[11]);
    font->glyph_pixels = data + ((data[14] << 8) + data[15]);
}
