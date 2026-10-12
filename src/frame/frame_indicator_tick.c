#include "frame_indicator.h"
void frame_indicator_tick(struct FrameObject *base)
{
 struct FrameIndicatorObject *object=(struct FrameIndicatorObject *)base;
 switch (object->state) {
 case 0:
  if (object->timed==1) {
   if (--object->duration==0xffff) transition_object_set_state(base,1);
  } else if (object->actor->flags&2) transition_object_set_state(base,1);
  break;
 case 1:object->flags|=2;break;
 }
}
asm(".align 2, 0");
