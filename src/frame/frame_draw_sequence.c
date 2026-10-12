#include "frame_render.h"
void frame_draw_sequence(struct FrameSpriteSequence *sequence, FrameU16 frame_index,
    FrameU8 options, struct FramePoint *origin, FrameU16 index,
    struct FrameOam *initial, struct FrameObject *base)
{
    struct FrameSpriteFrame *frame = (struct FrameSpriteFrame *)
        ((FrameU8 *)sequence + 12 + sequence->frame_offsets[frame_index]);
    struct FrameSpritePart *part = (struct FrameSpritePart *)
        ((FrameU8 *)frame + 10 + sequence->collider_count * 6 + sequence->attachment_count * 2);
    struct FrameRenderObject *object = (struct FrameRenderObject *)base;
    int scale_x = object->scale.x, scale_y = object->scale.y;
    unsigned int count = frame->count_flags & 0x1f;
    struct FrameOam oam;
    struct FramePoint dimensions;
    while (count) {
        int x, y, screen_y;
        oam = *initial;
        oam.tile = (FrameU16)(index + part->tile);
        oam.size = part->size;
        oam.shape = part->shape;
        frame_sprite_dimensions(oam.shape, oam.size, &dimensions);
        if (oam.display_mode == 0) {
            if (oam.flip_x == 1)
                x = -(part->x + dimensions.x);
            else
                x = part->x;
        } else {
            x = (part->x + dimensions.x / 2) * scale_x;
            if (x >= 0)
                x = ((FrameU32)x + g_frame_round_bias) >> 16;
            else
                x = -((g_frame_round_bias - x) >> 16);
            if (oam.display_mode == 3)
                x -= dimensions.x;
            else
                x -= dimensions.x / 2;
        }
        oam.x = origin->x + x;
        if (oam.display_mode == 0) {
            if (oam.flip_y < 0)
                y = -(part->y + dimensions.y);
            else if (options & 2) {
                y = -(part->y + dimensions.y);
                oam.flip_y = -1;
                oam.layer = g_frame_queue.deferred_refresh;
            } else
                y = part->y;
        } else {
            y = (part->y + dimensions.y / 2) * scale_y;
            if (y >= 0)
                y = ((FrameU32)y + g_frame_round_bias) >> 16;
            else
                y = -((g_frame_round_bias - y) >> 16);
            if (oam.display_mode == 3)
                y -= dimensions.y;
            else
                y -= dimensions.y / 2;
        }
        screen_y = origin->y + y;
        part++;
        if ((FrameU32)(screen_y + 64) <= 256) {
            oam.y = screen_y;
            frame_append_oam(g_frame_display_channel, &oam);
            if (options & 3)
                frame_note_oam(g_frame_display_channel - 1);
        }
        count--;
    }
}
