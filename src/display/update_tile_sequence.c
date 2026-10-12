#include "display.h"
void display_update_tile_sequence(const struct DisplayTileLayout *layout, const void *source,
    unsigned short first, unsigned short index, unsigned short bytes)
{
    unsigned int codec = display_tile_resource_codec(layout, index);
    void *destination = (void *)(0x06010000 + first * 32);
    unsigned int scratch;
    switch (codec) {
    case 0:
        display_cpu_copy_fast(source, destination, bytes >> 3);
        break;
    case 1:
        display_bios_swi_15(source, destination);
        break;
    case 2:
        g_display_tile_decompress(source, destination, &scratch);
        break;
    }
}
