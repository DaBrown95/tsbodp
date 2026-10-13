#include "frame_trigger_objects.h"

void frame_actor_trigger_step(struct FrameObject *base)
{
 struct FrameTriggerObject *object=(struct FrameTriggerObject *)base;
 struct FrameTriggerPayload *payload;
 switch(object->state) {
 case 0: break;
 case 1: object->flags|=2; break;
 case 2: break;
 case 3:
  if(--object->timer==-1) {
   object->flags|=4;
   transition_object_set_state((struct TransitionObject *)object,0);
  }
  break;
 case 4:
  payload=(struct FrameTriggerPayload *)resource_get_object_payload(object->owner_id,object->owner_slot);
  frame_trigger_actor_handoff(object->target,payload->argument0,(struct FrameObject *)object);
  object->timer=object->duration;
  transition_object_set_state((struct TransitionObject *)object,3);
  break;
 case 5:
  payload=(struct FrameTriggerPayload *)resource_get_object_payload(object->owner_id,object->owner_slot);
  frame_trigger_actor_handoff(object->target,payload->argument0,(struct FrameObject *)object);
  transition_object_set_state((struct TransitionObject *)object,1);
  break;
 }
}
asm(".align 2, 0");
