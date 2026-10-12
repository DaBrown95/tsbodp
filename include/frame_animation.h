#include "frame_render.h"
/* Animation record view inferred from its frame, command and collider readers. */
struct __attribute__((packed)) FrameCollider {
    FrameU8 x, y, width, height;
    signed char kind;
    FrameU8 unknown_05;
};
struct FrameAnimationState {
    FrameU8 delay, frame_delay, previous_frame, frame;
    struct FrameSpriteResource *resource;
    FrameU8 *commands, *command_start;
};
struct __attribute__((packed, aligned(2))) FrameAnimationBounds { FrameU16 x, y; };
struct FrameAnimationFrame {
    FrameU8 count_flags, unknown_01, width, height;
    FrameU16 bytes;
    struct FrameAnimationBounds bounds;
    FrameU8 following_records[1];
};
struct FrameAnimationPart {
    FrameU8 flags, palette, order, unknown_03;
    FrameU16 bytes, index;
    struct FrameSpriteVariant **variants;
};
struct FrameAnimationObject {
    FrameU8 unknown_00[12];
    FrameU32 flags;
    FrameU8 unknown_10[16];
    struct FramePoint next_position, velocity;
    FrameU8 unknown_30[31];
    FrameU8 pending_updates;
    FrameU8 unknown_50[95];
    FrameU8 collider_count;
    struct FrameCollider colliders[2];
    FrameU8 bound_x1, bound_x2, bound_y1, bound_y2;
    FrameU8 unknown_c0[16];
    union {
        struct FrameOam oam;
        struct {
            FrameU8 unknown_00[3];
            unsigned char unknown_03 : 4;
            signed char mirrored_x : 1;
            signed char mirrored_y : 1;
            unsigned char unknown_06 : 2;
        } flips;
    } display;
    struct FrameAnimationState animation;
    struct FramePoint scale;
    FrameU8 unknown_f0[12];
    FrameU16 bytes, index;
    FrameU8 strip_mode, sharing_flags, shared_group, requested_animation;
    struct FrameAnimationPart parts[4];
    FrameU8 variant_group, variant;
};
void frame_decode_animation_commands(struct FrameObject *);
void frame_refresh_animation_bounds(struct FrameObject *);
void frame_refresh_part_colliders(struct FrameObject *);
FrameU32 audio_play_animation_cue(FrameU32);
FrameU16 frame_random_bounded(FrameU16);
