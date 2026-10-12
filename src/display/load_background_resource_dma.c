#include "display.h"
static inline void *character_destination(const struct BackgroundCharacterBase *base) {
    register const struct BackgroundCharacterBase *pointer asm("r1") = base;
    register unsigned int offset asm("r0") = pointer->character_base << 14;
    return (void *)(offset + 0x06000000);
}
const unsigned short *display_load_background_resource_dma(unsigned int index,
    const struct BackgroundResource *resource, unsigned short tile_offset)
{
    const unsigned char *data;
    const unsigned short *dimensions = 0;
    register struct BackgroundState *background asm("r8");
    unsigned int count, palette_bytes;
    int elements;
    register void *destination asm("r3");
    background = &g_background_states[index];
    data = (const unsigned char *)resource + 2;
    if (resource->flags & 1)
        palette_bytes = 512;
    else
        palette_bytes = (unsigned char)(resource->flags & 2) ? 32 : 0;
    data += palette_bytes;
    if (resource->flags & 4) {
        count = *(const unsigned short *)data;
        data += 2;
        DISPLAY_DMA3->source = (unsigned int)data;
        DISPLAY_DMA3->destination = 0x06000000;
        DISPLAY_DMA3->control = (count >> 1) | 0x80000000;
        DISPLAY_DMA3->control;
    }
    if (resource->flags & 0x10) {
        if (resource->flags & 8) {
            dimensions = (const unsigned short *)data;
            elements = dimensions[0] * dimensions[1];
            if (elements & 1)
                ++elements;
            if (resource->palette_bank & 1)
                elements /= 2;
            data = (const unsigned char *)dimensions + (elements * 2 + 4);
        }
        destination = (void *)character_destination((const void *)background);
        if (!(resource->flags & 0x80))
            destination = (unsigned char *)destination + (tile_offset << 5);
        else
            destination = (unsigned char *)destination + (tile_offset << 6);
        count = *(const unsigned short *)data;
        data += 2;
        display_decode_background(resource, data, count, destination);
    }
    return dimensions;
}
