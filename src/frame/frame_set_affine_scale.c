#include "frame_affine.h"
void frame_set_affine_scale(struct FrameAffineObject *object, int x, int y, int angle)
{
    FrameU16 rotation = angle;
    FrameU16 slot, reciprocal_x, reciprocal_y;
    object->scale_x = x;
    object->scale_y = y;
    object->rotation = rotation;
    slot = frame_ensure_affine_slot(object);
    reciprocal_x = 0x1000000 / x;
    reciprocal_y = 0x1000000 / y;
    if (!reciprocal_x)
        reciprocal_x = 1;
    if (!reciprocal_y)
        reciprocal_y = 1;
    g_frame_affine_parameters[slot].scale_x = reciprocal_x;
    g_frame_affine_parameters[slot].scale_y = reciprocal_y;
    g_frame_affine_parameters[slot].rotation = rotation;
    object->display.display_mode = 1;
}
