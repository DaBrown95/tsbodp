#include "display_text_measure.h"
int display_text_glyph_width(const struct DisplayFont *font,unsigned short glyph)
{
    int width=0;
    if(glyph) {
        int index=glyph-font->first;
        if(index>=0 && index<=font->last-font->first) width=font->widths[index];
        else width=font->widths[1];
    }
    return width;
}

__asm__(".align 2, 0");
