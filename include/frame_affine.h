#include "frame_render.h"
struct FrameAffineObject {
    FrameU8 unknown_00[208];
    struct FrameOam display;
    FrameU8 unknown_d8[16];
    int scale_x, scale_y, step_x, step_y;
    short rotation;
    FrameU16 frames;
};
struct FrameAffineParameters { FrameU16 scale_x, scale_y, rotation, unknown_06; };
extern struct FrameAffineParameters g_frame_affine_parameters[];
FrameU32 frame_ensure_affine_slot(struct FrameAffineObject *);
FrameU32 frame_get_affine_slot(struct FrameOam *);
void frame_set_affine_slot(struct FrameOam *, FrameU16);
void frame_free_affine_slot(FrameU16);
void frame_set_affine_scale(struct FrameAffineObject *, int, int, int);

FrameU32 frame_allocate_affine_slot(void);
extern FrameU8 g_frame_affine_slots[32];
extern FrameU8 g_frame_affine_slot_count;
struct FrameAffineSlotFields { FrameU16 attr_y, attr_x; };

extern unsigned char *g_oam_previous;
void frame_write_affine_matrices(struct FrameAffineParameters *, unsigned char *, FrameU32, FrameU32);
