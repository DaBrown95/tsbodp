#include "display_catalog_presentation.h"
#include "display_text_raster.h"

void display_text_set_line_height(int height)
{
    g_display_text_state.line_height = height;
}
asm(".align 2, 0");
