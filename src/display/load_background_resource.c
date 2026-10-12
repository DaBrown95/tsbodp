#include "display.h"
const unsigned short *display_load_background_resource(unsigned int index,
    const struct BackgroundResource *resource, unsigned short tile_offset,
    unsigned short palette_offset)
{
    const unsigned char *data;
    const unsigned short *dimensions = 0;
    struct BackgroundState *background;
    unsigned int count;
    int elements;
    void *destination;
    background = &g_background_states[index];
    data = (const unsigned char *)resource + 2;
    data += display_load_resource_palette(resource, palette_offset);
    if (resource->flags & 4) {
        count = *(const unsigned short *)data;
        data += 2;
        display_cpu_copy(data, (void *)0x06000000, count >> 1);
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
        destination = (void *)(0x06000000 +
            (((const struct BackgroundCharacterBase *)background)->character_base << 14));
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
