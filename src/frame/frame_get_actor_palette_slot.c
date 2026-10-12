#include "frame_actor_runtime.h"
unsigned int frame_get_actor_palette_slot(struct FrameObject *object)
{
 return ((struct FrameActorObject *)object)->oam.palette;
}
