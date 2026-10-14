#include "display.h"
#include "display_palette_lifecycle.h"

void display_initialize_palettes(void)
{
    g_palette_curve_parameter = -257;
    display_configure_palette_curve(256);
    display_initialize_palette_pair(&g_palette_buffer_pairs[0],
        (unsigned short *)0x05000000);
    display_initialize_palette_pair(&g_palette_buffer_pairs[1],
        (unsigned short *)0x05000200);
    display_reset_palette_jobs();
}
