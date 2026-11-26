#include "frame_render.h"
#include "input.h"

/* Index and multipart traversal use the same native pointer register. */
union RenderR6Pointer {
    const FrameU16 *index;
    struct FrameRenderPart *part;
};

FrameU8 frame_render_object(struct FrameObject *base)
{
    register struct FrameRenderObject *object = (struct FrameRenderObject *)base;
    struct FrameOam *object_oam = &object->display.oam;
    struct FrameOam initial = *object_oam;
    struct FramePoint origin;
    struct FramePoint position = object->next_position;
    FrameU32 flags = object->flags;
    int options = (object->sharing_flags & 0x80) ? (2) : (0);
    int tile;
    int result;
    unsigned int i;
    unsigned int count;
    unsigned int part_index;
    unsigned int variant_offset;
    register union RenderR6Pointer stage_pointer;
    int order;
    FrameU8 *previous_frame;
    FrameU8 *current_frame;
    const FrameU16 *index_address;
    struct FrameSpriteSequence *sequence;
    if (!(flags & 0x40000000))
        return 0;
    {
        unsigned int observed_index;
        register unsigned int invalid_index;
        stage_pointer.index = &object->index;
        observed_index = *stage_pointer.index;
        invalid_index = 0xffff;
        index_address = stage_pointer.index;
        if (observed_index == invalid_index)
            return 2;
    }
    if (!object->strip_mode) {
        struct FrameOam oam;
        if (flags & 0x200000) {
            origin.x = position.x >> 16;
            origin.y = position.y >> 16;
        } else {
            frame_get_view_origin(&origin, g_input_config.local_player);
            origin.x = (position.x >> 16) - origin.x;
            origin.y = (position.y >> 16) - origin.y;
            initial.x = origin.x;
            initial.y = origin.y;
            *object_oam = initial;
        }
        result = 1;
        if (flags & 0x100) {
            struct FramePoint dimensions;
            struct FrameSpriteFrame *sprite_frame;
            struct FrameSpritePart *tile_part;
            sequence = object->graphic.resource->sequence;
            sprite_frame = (struct FrameSpriteFrame *)((((FrameU8 *)sequence) + 12) +
                                                       sequence->frame_offsets[object->frame]);
            count = sprite_frame->count_flags & 0x1f;
            tile_part = (struct FrameSpritePart *)(((((FrameU8 *)sprite_frame) + 10) +
                                                    (sequence->collider_count * 6)) +
                                                   (sequence->attachment_count * 2));
            tile = (sprite_frame->tile_bytes >> 5) + (*index_address);
            i = 0;
            current_frame = &object->frame;
            previous_frame = &object->previous_frame;
            for (; i < count; i++) {
                oam = initial;
                oam.tile = (FrameU16)(tile + tile_part->tile);
                oam.size = tile_part->size;
                oam.shape = tile_part->shape;
                if (object->display.oam.display_mode == 3) {
                    oam.x = origin.x + (tile_part->x * 2);
                    oam.y = origin.y + (tile_part->y * 2);
                } else if (object->display.oam.display_mode == 1) {
                    oam.x = origin.x + tile_part->x;
                    oam.y = origin.y + tile_part->y;
                } else {
                    frame_sprite_dimensions(oam.shape, oam.size, &dimensions);
                    if (oam.flip_x == 1)
                        oam.x = (origin.x - tile_part->x) - dimensions.x;
                    else
                        oam.x = origin.x + tile_part->x;
                    if (oam.flip_y < 0)
                        oam.y = (origin.y - tile_part->y) - dimensions.y;
                    else
                        oam.y = origin.y + tile_part->y;
                }
                tile_part++;
                if (object->sharing_flags & 0x20)
                    frame_note_oam(g_frame_display_channel);
                frame_append_oam(g_frame_display_channel, &oam);
            }

            *previous_frame = *current_frame;
        } else {
            /* The const cell preserves the pinned compiler's native status spill. */
            const int status[1] = {result + 1};
            if (object->sharing_flags & 0x40) {
                order = 7;
                do {
                    register struct FrameSpriteVariant ***variants;
                    part_index = 0;
                    /* Keep the two real traversal strides independent. */
                    variant_offset = 0;
                    {
                        do {
                            stage_pointer.part = &object->parts[part_index];
                            variants =
                                (struct FrameSpriteVariant **
                                     *)(((FrameU8 *)(&object->parts[0].variants)) + variant_offset);
                            {
                                register struct FrameSpriteVariant ***reader_r3 asm("r3") =
                                    variants;
                                struct FrameSpriteVariant **rows = *reader_r3;
                                if (rows && (stage_pointer.part->order == order)) {
                                    int group;
                                    int variant;
                                    int wrap_previous;
                                    FrameU8 part_flags;
                                    int part_frame;
                                    oam = initial;
                                    group = object->variant_group;
                                    variant = object->variant;
                                    if (stage_pointer.part->flags & 1)
                                        options |= 1;
                                    else
                                        options &= ~1;
                                    {
                                        struct FrameOam *output = &oam;
                                        output->palette = stage_pointer.part->palette;
                                    }
                                    {
                                        register struct FrameSpriteVariant ***reader_r1 asm("r1") =
                                            variants;
                                        sequence = (*reader_r1)[group][variant].sequence;
                                    }
                                    part_flags = stage_pointer.part->flags;
                                    wrap_previous = (FrameU8)(part_flags & 4);
                                    if (wrap_previous)
                                        goto previous_variant_frame;
                                    {
                                        register FrameU8 delayed_frame asm("r0") = part_flags & 8;
                                        if (!delayed_frame)
                                            goto current_variant_frame;
                                    }
                                previous_variant_frame: {
                                    part_frame = object->frame - 1;
                                    if (part_frame < 0) {
                                        if (wrap_previous)
                                            part_frame = sequence->frame_count - 1;
                                        else
                                            part_frame = 0;
                                    }
                                }

                                    goto variant_frame_ready;
                                current_variant_frame:
                                    part_frame = object->frame;

                                variant_frame_ready: {
                                    register struct FrameSpriteVariant ***reader_r4 asm("r4") =
                                        variants;
                                    struct FrameSpriteSequence *draw_sequence =
                                        (*reader_r4)[group][variant].sequence;
                                    frame_draw_sequence(draw_sequence, part_frame, options, &origin,
                                                        stage_pointer.part->index, &oam,
                                                        (struct FrameObject *)object);
                                }
                                }
                            }
                            variant_offset += sizeof(struct FrameRenderPart);
                        } while ((++part_index) <= 3);
                        --order;
                    }
                } while (order >= 0);
            } else {
                oam = initial;
                if (object->sharing_flags & 0x20)
                    options |= 1;
                else
                    options &= ~1;
                frame_draw_sequence(object->graphic.resource->sequence, object->frame, options,
                                    &origin, *index_address, &oam, (struct FrameObject *)object);
            }
            result = status[0];
        }
    } else {
        frame_get_view_origin(&origin, g_input_config.local_player);
        object->display.hardware.x = ((short)(object->next_position.x >> 16)) - origin.x;
        *((FrameU8 *)object_oam) = ((short)(object->next_position.y >> 16)) - origin.y;
        object->display.hardware.tile = *stage_pointer.index;
        count = object->graphic.strip_count;
        while (count) {
            if (object->sharing_flags & 0x20)
                frame_note_oam(g_frame_display_channel);
            frame_append_oam(g_frame_display_channel, &object->display.oam);
            object->display.hardware.x += 32;
            object->display.hardware.tile += object->display.oam.size * 4;
            count--;
        }

        result = 1;
    }
    return result;
}
