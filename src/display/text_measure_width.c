#include "display_text_measure.h"
int display_text_measure_width(const char *text)
{
    const unsigned char *cursor=(const unsigned char *)text;
    int width=0;
    while(*cursor) {
        if(*cursor=='@') {
            ++cursor;
            width+=display_text_measure_width((char*)g_display_text_substitutions[*cursor]);
        }else {
            const struct DisplayFont *font;
            if(*(volatile const unsigned char *)cursor>0xef) {++cursor; font=g_display_fonts[1];}
            else font=g_display_fonts[0];
            width+=display_text_glyph_width(font,*cursor);
        }
        ++cursor;
    }
    return width;
}

__asm__(".align 2, 0");
