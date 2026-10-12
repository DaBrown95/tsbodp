#include "frame_scene_motion.h"
void frame_set_velocity(struct FrameObject *object,int x,int y)
{
 object->velocity.x=x;
 object->velocity.y=y;
}
asm(".align 2, 0");
