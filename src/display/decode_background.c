#include "display.h"
void display_decode_background(const struct BackgroundResource *resource,
                               const void *source, int bytes, void *destination)
{
    switch (((const struct BackgroundResourceCodec *)resource)->codec) {
    case 0:
        display_cpu_copy(source, destination, ((unsigned int)(bytes / 2) << 11) >> 11);
        break;
    case 1:
        display_bios_swi_15(source, destination);
        break;
    case 2:
        display_bios_swi_12(source, destination);
        break;
    case 3:
        g_display_background_decompress(source, destination, 0);
        break;
    }
}
