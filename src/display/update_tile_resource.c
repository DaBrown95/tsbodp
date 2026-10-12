#include "display.h"
void display_update_tile_resource(struct DisplayTileObject *object, const void *source)
{
    unsigned int codec = display_tile_resource_codec((const struct DisplayTileLayout *)object->resource->layout, object->frame_index);
    void *destination = (void *)(0x06010000 + object->first_tile * 32);
    unsigned int bytes;
    switch (codec) {
    case 0:
        { unsigned int transfer_bytes = object->bytes;
        if (object->double_tile_size >= 0)
            transfer_bytes >>= 1;
        bytes = transfer_bytes; }
        display_cpu_copy_fast(source, destination, bytes >> 2);
        break;
    case 1:
        display_lz77_vram(source, destination);
        break;
    case 2:
        g_display_tile_decompress(source, destination, &bytes);
        break;
    }
}
