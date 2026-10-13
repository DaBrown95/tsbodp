#include "frame_optional_view.h"
void frame_optional_view_step(struct FrameObject *base)
{
 struct FrameOptionalViewObject *object=(struct FrameOptionalViewObject *)base;
 /* The addressed position and separate configuration retain two point lifetimes. */
 struct FramePoint position,configuration; struct FramePoint *point=&position;
 struct FrameActorObject *actor;
 switch(object->state){
 case 0:break;
 case 1:object->flags|=0x82;break;
 case 4:{
  actor=(struct FrameActorObject *)object->actor;
  transition_run_second(0x3f,object->first_transition);
  actor->variant_state=1;
  object->delay=1;
  point->x=(unsigned int)object->view_x<<16;
  point->y=(unsigned int)object->view_y<<16;
  transition_set_view_mode(1,g_optional_view_context.current_view);
  { unsigned char view=g_optional_view_context.current_view; transition_set_view_position(*point,view); }
  actor->position=actor->next_position=*point;
  actor->direction=object->actor_direction;
  actor->pending_updates|=0x10;
  if(!object->resource_loaded){
   struct FrameOptionalViewPayload *payload=(struct FrameOptionalViewPayload *)resource_get_object_payload(object->owner_id,object->owner_slot);
   resource_activate_groups(payload->objects_group,payload->program_group);
   object->resource_loaded=1;
  }
  object->state=5;
  break;
 }
 case 5:
  if(--object->delay==65535){
   actor=(struct FrameActorObject *)object->actor;
   actor->variant_state=2;
   actor->flags|=0x10;
   configuration.x=16; configuration.y=16;
   transition_set_view_mode(0,0);
   transition_configure_view((struct TransitionViewObject *)actor,configuration,0);
   transition_run_first(0x3f,object->second_transition);
   object->actor=0;
   object->state=0;
   frame_enable_object_flags(base,4);
  }
  break;
 }
}
