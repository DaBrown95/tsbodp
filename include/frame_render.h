#ifndef FRAME_RENDER_H
#define FRAME_RENDER_H

#include "frame.h"
/* Independent record view for the frame/render path; offsets are provisional. */
struct FrameOam {
    unsigned int y : 8;
    unsigned int display_mode : 2;
    unsigned int gfx_mode : 2;
    unsigned int mosaic : 1;
    unsigned int double_tile_size : 1;
    unsigned int shape : 2;
    unsigned int x : 9;
    unsigned int affine_index : 3;
    unsigned int flip_x : 1;
    signed int flip_y : 1;
    unsigned int size : 2;
    unsigned int tile : 10;
    unsigned int layer : 2;
    unsigned char palette : 4;
    FrameU16 padding;
};
struct __attribute__((packed)) FrameSpritePart {
    signed int x : 9;
    signed int y : 9;
    unsigned int size : 2;
    unsigned int shape : 2;
    unsigned int tile : 10;
};
struct FrameSpriteSequence {
    FrameU8 unknown_00[6];
    FrameU16 frame_count;
    FrameU16 unknown_08;
    FrameU8 attachment_count, collider_count;
    /* GNU89 variable tail; total serialized capacity is not established here. */
    FrameU16 frame_offsets[0];
};
struct __attribute__((packed, aligned(2))) FrameSpriteFrame {
    FrameU8 count_flags, unknown_01, width, height;
    FrameU16 tile_bytes;
    short bound_x, bound_y;
    FrameU8 following_records[0];
};
struct FrameSpriteResource {
    FrameU32 unknown_00;
    struct FrameSpriteSequence *sequence;
};
struct FrameSpriteVariant {
    FrameU32 unknown_00;
    struct FrameSpriteSequence *sequence;
    FrameU32 unknown_08[2];
};
struct FrameRenderPart {
    FrameU8 flags;
    FrameU8 palette, order, unknown_03;
    FrameU16 bytes, index;
    struct FrameSpriteVariant **variants;
};
struct FrameRenderObject {
    FrameU8 unknown_00[12];
    FrameU32 flags;
    FrameU8 unknown_10[16];
    struct FramePoint next_position;
    FrameU8 unknown_28[168];
    union {
        struct FrameOam oam;
        struct {
            FrameU8 y, attributes;
            unsigned short x : 9;
            unsigned short unknown_x : 7;
            unsigned short tile : 10;
            unsigned short unknown_tile : 6;
            FrameU16 padding;
        } hardware;
    } display;
    FrameU8 delay, frame_delay, previous_frame, frame;
    union {
        struct FrameSpriteResource *resource;
        FrameU16 strip_count;
    } graphic;
    FrameU8 unknown_e0[8];
    struct FramePoint scale;
    FrameU8 unknown_f0[12];
    FrameU16 bytes, index;
    FrameU8 strip_mode, sharing_flags, shared_group, unknown_103;
    struct FrameRenderPart parts[4];
    signed char variant_group, variant;
};
extern FrameU8 g_frame_display_channel;
void frame_sprite_dimensions(int, int, struct FramePoint *);
int frame_append_oam(FrameU8, struct FrameOam *);
void frame_note_oam(int);
void frame_draw_sequence(struct FrameSpriteSequence *, FrameU16, FrameU8,
    struct FramePoint *, FrameU16, struct FrameOam *, struct FrameObject *);

extern FrameU32 g_frame_round_bias;
struct FrameAllocationShared {
    FrameU32 unknown_00;
    struct FrameSpriteResource *resource;
    FrameU16 indices[12];
    FrameU8 counts[12];
    FrameU8 frame, unknown_2d[3];
    FrameU32 epoch;
};
extern FrameU32 g_frame_allocation_epoch;
void frame_object_dimensions(struct FrameObject *, struct FramePoint *);
void frame_part_dimensions(struct FrameObject *, struct FramePoint *, FrameU8);
const void *frame_object_pixels(struct FrameObject *);
const void *frame_part_pixels(struct FrameObject *, FrameU8);
FrameU32 frame_allocate_display(const void *, FrameU32, FrameU32);
void frame_upload_display(struct FrameObject *, const void *);
void frame_upload_sequence(struct FrameSpriteSequence *, const void *, FrameU16, FrameU16, FrameU16);

#endif
