#include "frame_affine.h"
void frame_destroy_affine(struct FrameObject *base)
{
    struct FrameAffineObject *object = (struct FrameAffineObject *)base;
    if (object->display.display_mode == 1 || object->display.display_mode == 3) {
        FrameU16 slot;
        struct FrameOam *oam;
        object->display.display_mode = 0;
        oam = &object->display;
        slot = frame_get_affine_slot(oam);
        frame_set_affine_slot(oam, 0);
        frame_free_affine_slot(slot);
    }
}
