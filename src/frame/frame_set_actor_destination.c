#include "frame_actor_runtime.h"
void frame_set_actor_destination(struct FrameObject *object,const struct FramePoint *point)
{
 object->destination.x=point->x<<16;
 object->destination.y=point->y<<16;
}
asm(".align 2, 0");
