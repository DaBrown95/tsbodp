#include "frame_scene_motion.h"

void frame_set_oriented_velocity_y(struct FrameObject *object, int velocity)
{
    if (object->render_reverse_y < 0)
        velocity = 0u - (unsigned int)velocity;
    object->velocity.y = velocity;
}
asm(".align 2, 0");
