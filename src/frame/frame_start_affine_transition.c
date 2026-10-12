#include "frame_affine.h"
void frame_start_affine_transition(struct FrameAffineObject *object, int x, int y, int frames)
{
    if (frames) {
        object->step_x = (x - object->scale_x) / frames;
        object->step_y = (y - object->scale_y) / frames;
        object->frames = frames;
    }
}
