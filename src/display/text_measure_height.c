#include "display_text_measure.h"
int display_text_measure_height(const char *text)
{
    int height=0;
    if(*text) height=g_display_fonts[0]->height;
    return height;
}
