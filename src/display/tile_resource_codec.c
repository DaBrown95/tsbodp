#include "display.h"
unsigned char display_tile_resource_codec(const struct DisplayTileLayout *layout, unsigned short index)
{
    unsigned int offset = layout->record_offsets[index];
    const struct DisplayTileRecord *record;
    offset += 12;
    record = (const struct DisplayTileRecord *)((const unsigned char *)layout + offset);
    if (record->flags & 0x20)
        return 1;
    if (record->flags & 0x40)
        return 2;
    return 0;
}
__asm__(".align 2, 0");
