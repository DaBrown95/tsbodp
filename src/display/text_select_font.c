#include "display_text_raster.h"

void display_text_select_font(unsigned int group, int palette, int fill)
{
    g_display_text_state.font = &g_display_font_banks[group][0];
    g_display_text_state.alternate_font = &g_display_font_banks[group][1];
    g_display_text_state.line_height = g_display_text_state.font->line_advance;
    if (g_display_text_state.wide_color == 1) {
        g_display_text_state.palette_base = palette;
        g_display_text_state.palette_bits = 0;
    } else {
        g_display_text_state.palette_base = palette & 15;
        g_display_text_state.palette_bits = ((unsigned int)(palette >> 4)) << 12;
    }
    g_display_text_state.fill = fill;
}
