#include "frame_render.h"

/* Direct object view used by the frame tile-allocation handoff. */
struct FrameApplyPart {
    FrameU8 flags, palette, order, unknown_03;
    FrameU16 bytes, index;
    struct FrameSpriteVariant **variants;
};
struct FrameApplyObject {
 FrameU8 unknown_00[12];
 FrameU32 flags;
 FrameU8 unknown_10[192];
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
 unsigned short tile : 10;
 unsigned short layer : 2;
 unsigned short palette : 4;
 FrameU16 padding;
 FrameU8 delay,frame_delay,previous_frame,frame;
 struct FrameSpriteResource *resource;
 FrameU8 unknown_e0[28];
 FrameU16 bytes,index;
 FrameU8 strip_mode,sharing_flags,shared_group,unknown_103;
 struct FrameApplyPart parts[4];
 signed char variant_group,variant;
};
