#include "display.h"
unsigned int display_allocate_tile_bytes(struct DisplayTileResource *resource,
                                        unsigned int bytes, unsigned int small_tiles)
{
    unsigned int count, result;
    unsigned int (*allocator)(unsigned int *, unsigned int, unsigned int);
    allocator = (unsigned int (*)(unsigned int *, unsigned int, unsigned int))0x03007390;
    if (!small_tiles) {
        count = bytes >> 6;
        result = allocator(g_display_allocated_tiles, count, 0);
    } else {
        count = bytes >> 5;
        result = allocator(g_display_allocated_tiles, count, 0);
    }
    if (result != 0xffff) {
        display_mark_tiles_allocated((unsigned short)result, (unsigned short)count);
        if (resource) {
            if (!small_tiles)
                display_copy_tile_resource(resource, (unsigned short)result);
            else
                display_copy_tile_resource(resource, (unsigned short)result);
        }
    }
    return result;
}
