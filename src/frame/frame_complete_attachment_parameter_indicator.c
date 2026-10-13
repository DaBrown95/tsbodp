#include "frame_actor_attachment_parameters.h"
void frame_complete_attachment_parameter_indicator(struct FrameObject *object)
{
 struct FrameTransientEffect *effect=frame_create_transient_effect(6,0,3);
 if(effect) {
  effect->owner=((struct FrameActorObject *)object)->indicator;
  effect->position=object->position;
  effect->phase=3;
  effect->flags|=0x248a;
  effect->height=60;
  effect->enabled=1;
  effect->countdown=1;
  effect->unknown34=0;
  effect->direction=0;
  effect->rate=0x10000;
  effect->offset_x=5;
  effect->offset_y=20;
 }
}
