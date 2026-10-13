#include "display_transient_definition.h"

unsigned short frame_initialize_transient_definition(unsigned char bank,
                                                    unsigned char slot,
                                                    struct FrameSpriteResource *resource)
{
    unsigned short bytes = 0;
    struct FrameSpriteSequence *sequence = resource->sequence;
    unsigned char frame = 0;

    while (frame < resource->sequence->frame_count) {
        const struct FrameSpriteFrame *record;
        g_frame_transient_definitions[bank][slot].frames[frame] = bytes >> 6;
        record = (const struct FrameSpriteFrame *)((unsigned char *)sequence +
            12 + sequence->frame_offsets[frame]);
        bytes += record->width * record->height;
        ++frame;
    }
    {
        unsigned int allocation = display_allocate_tile_bytes(
            (struct DisplayTileResource *)resource, bytes, 0);
        unsigned int table_address = (unsigned int)g_frame_transient_definitions;
        struct FrameTransientDefinition *record =
            (struct FrameTransientDefinition *)(slot * 40 + bank * 320 + table_address);
        record->unknown26 = allocation;
        record->frame_count = resource->sequence->frame_count;
        record->resource = resource;
        record->index = record->unknown26;
        return record->index;
    }
}

asm(".align 2, 0");
