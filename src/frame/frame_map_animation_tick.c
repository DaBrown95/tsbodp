#include "frame_map_animation.h"

void frame_map_animation_tick(struct FrameObject *base) {
 struct FrameMapAnimationObject *object=(struct FrameMapAnimationObject *)base;
 struct FrameMapAnimationPayload *payload;
 unsigned char once;
 unsigned char *signal,*pending;
 switch(object->state) {
 case 0: {
  unsigned int enabled=object->enabled;
  signal=&object->signal;pending=&object->pending;
  if(!enabled)break;
  if(object->polarity==0) {if(object->reverse!=0)break;}
  else if(object->reverse==0)break;
  transition_object_set_state((struct TransitionObject *)object,4);
  break;
 }
 case 1: {
  payload=(struct FrameMapAnimationPayload *)resource_get_object_payload(object->owner_group,object->owner_slot);
  resource_activate_groups(payload->group,payload->slot);
  object->flags|=2;
  signal=&object->signal;pending=&object->pending;
  break;
 }
 case 4: {
  unsigned int signaled=object->signal;
  signal=&object->signal;pending=&object->pending;
  if(signaled) {
   if((*pending&1)&&object->latched) {
    object->latched=0;
    transition_object_set_state((struct TransitionObject *)object,0);
    *signal=0;
    break;
   }
   if(object->reverse) {object->latched=1;*signal=0;break;}
  }
  if(object->sound && !object->started)audio_game_sample_active(g_frame_map_animation_sample);
  if(object->reverse) {
   if(object->current<object->last) {
    if(--object->timer==255) {object->timer=object->period;frame_map_animation_write_rectangle((struct FrameObject *)object);}
    break;
   }
   once=object->one_shot;
   if(once) {transition_object_set_state((struct TransitionObject *)object,1);break;}
   {
    payload=(struct FrameMapAnimationPayload *)resource_get_object_payload(object->owner_group,object->owner_slot);
    resource_activate_groups(payload->group,payload->slot);
   }
   object->current=object->last-object->step;
   object->reverse=0;
  } else {
   if(object->current>object->first) {
    if(--object->timer==255) {
     object->timer=object->period;
     object->current-=object->step;
     frame_map_animation_write_rectangle((struct FrameObject *)object);
     object->current-=object->step;
    }
    break;
   }
   once=object->one_shot;
   if(once) {transition_object_set_state((struct TransitionObject *)object,1);break;}
   {
    payload=(struct FrameMapAnimationPayload *)resource_get_object_payload(object->owner_group,object->owner_slot);
    resource_activate_groups(payload->group,payload->slot);
   }
   object->reverse=1;
  }
  transition_object_set_state((struct TransitionObject *)object,0);
  if(object->started)object->started=once;
  break;
 }
 default:frame_run_actor_state((struct FrameObject *)object);
  signal=&object->signal;pending=&object->pending;
  break;
 }
 *pending=0;*signal=0;
}
asm(".align 2, 0");
