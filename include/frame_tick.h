#include "frame_animation.h"
struct FrameAnimationCore {
    FrameU8 delay, frame_delay, previous_frame, frame;
    struct FrameSpriteResource *resource;
};
struct FrameTickObject {
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
    FrameU8 delay, frame_delay, previous_frame, frame;
    struct FrameSpriteResource *resource;
    FrameU8 *commands, *command_start;
    struct FramePoint scale;
    FrameU8 unknown_f0[12];
    FrameU16 bytes, index;
    FrameU8 strip_mode, sharing_flags, shared_group, requested_animation;
    struct FrameAnimationPart parts[4];
    FrameU8 variant_group, variant;
};
