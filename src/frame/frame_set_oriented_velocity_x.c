#include "frame_scene_motion.h"

void frame_set_oriented_velocity_x(struct FrameObject *object, int velocity)
{
    if (object->render_special < 0)
        velocity = 0u - (unsigned int)velocity;
    object->velocity.x = velocity;
}
asm(".align 2, 0");
