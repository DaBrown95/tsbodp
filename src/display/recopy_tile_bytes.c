#include "display_transient_definition.h"

unsigned int display_recopy_tile_bytes(struct DisplayTileResource *resource,
                                      unsigned int bytes,
                                      unsigned char small_tiles,
                                      unsigned short first)
{
    if (resource) {
        if (!small_tiles)
            display_copy_tile_resource(resource, first);
        else
            display_copy_tile_resource(resource, first);
    }
    return first;
}

asm(".align 2, 0");
