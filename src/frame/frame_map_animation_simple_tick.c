#include "frame_map_animation.h"

void frame_map_animation_simple_tick(struct FrameObject *base) {
 struct FrameMapAnimationObject *object=(struct FrameMapAnimationObject *)base;
 switch(object->state) {
 case 0: break;
 case 1: object->flags|=2;break;
 case 4:
  if(--object->timer==255) {
   object->timer=object->period;
   frame_map_animation_write_rectangle(base);
   if(object->one_shot) {
    if(object->current>=object->last)transition_object_set_state((struct TransitionObject *)object,1);
   } else if(object->current>=object->last) {
    object->current=object->first;
    if(object->reverse==0)transition_object_set_state((struct TransitionObject *)object,0);
   }
  }
  break;
 }
}
asm(".align 2, 0");
