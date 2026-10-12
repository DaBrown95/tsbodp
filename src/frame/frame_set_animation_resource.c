#include "frame_tick.h"
void frame_set_animation_frame(struct FrameTickObject *, FrameU8);
void frame_set_animation_resource(struct FrameObject *base, struct FrameSpriteResource *resource)
{
 struct FrameTickObject *object=(struct FrameTickObject *)base;
 if (object->resource != resource) {
  object->resource=resource;
  object->flags |= 0x80;
 }
 frame_set_animation_frame(object,0);
}
