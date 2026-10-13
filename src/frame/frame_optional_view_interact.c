#include "frame_optional_view.h"
void frame_optional_view_interact(struct FrameObject *base,struct FrameObject *actor)
{
 if(actor->id==0){
  ((struct FrameOptionalViewObject *)base)->state=4;
  frame_disable_object_flags(base,4);
  ((struct FrameOptionalViewObject *)base)->actor=actor;
 }
}
