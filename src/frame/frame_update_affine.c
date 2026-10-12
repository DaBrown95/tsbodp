#include "frame_affine.h"
void frame_update_affine(struct FrameObject *base)
{
    struct FrameAffineObject *object = (struct FrameAffineObject *)base;
    object->frames--;
    object->scale_x += object->step_x;
    object->scale_y += object->step_y;
    frame_set_affine_scale(object, object->scale_x >> 8, object->scale_y >> 8, object->rotation);
}
asm(".align 2, 0");
