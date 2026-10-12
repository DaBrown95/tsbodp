#include "display.h"

const unsigned char *display_object_tile_pixels(struct DisplayTileObject *object)
{
    const struct DisplayTileResource *resource = object->resource;
    const struct DisplayTileLayout *layout = (const struct DisplayTileLayout *)resource->layout;
    unsigned int index = object->frame_index;
    unsigned int offset = layout->record_offsets[index];
    const struct DisplayTileRecord *record;
    offset += (unsigned int)layout;
    record = (const struct DisplayTileRecord *)(offset + 12);
    return resource->data + record->data_offset;
}
