#include "display_transient_definition.h"

unsigned short frame_reload_transient_definition(unsigned char bank,
                                                unsigned char slot,
                                                struct FrameSpriteResource *resource)
{
    unsigned short bytes = 0;
    struct FrameSpriteSequence *sequence = resource->sequence;
    unsigned char frame = 0;

    while (frame < resource->sequence->frame_count) {
        const struct FrameSpriteFrame *record;
        g_frame_transient_definitions[bank][slot].frames[frame] = bytes;
        record = (const struct FrameSpriteFrame *)((unsigned char *)sequence +
            12 + sequence->frame_offsets[frame]);
        bytes += record->width * record->height;
        ++frame;
    }
    {
        struct FrameTransientDefinition *record =
            (struct FrameTransientDefinition *)(slot * 40 + bank * 320 +
                (unsigned int)g_frame_transient_definitions);
        record->frame_count = resource->sequence->frame_count;
        record->unknown26 = bytes;
        record->resource = resource;
        display_recopy_tile_bytes((struct DisplayTileResource *)resource, bytes,
                                  0, record->index);
        return record->index;
    }
}

asm(".align 2, 0");
