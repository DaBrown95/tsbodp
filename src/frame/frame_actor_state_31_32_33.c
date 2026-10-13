#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_choices.h"
void frame_actor_state_31_32_33(struct FrameObject *object)
{
 struct FrameObject *target;
 unsigned int action;
 struct FramePoint point;
 unsigned char result;
 switch(((struct FrameActorObject *)object)->variant_state) {
 case 2:
  result=0;
  while(frame_find_pending_action(g_actor_choice_categories[((struct FrameActorObject *)object)->actor_id],&target,&action)==1) {
   result=frame_actor_use_target(target,object,action);
   if(result==1) {
    ((struct FrameActorObject *)object)->reset=1;
    if(((struct FrameActorObject *)object)->actor_id==4)audio_play_animation_cue(51);
    break;
   }
  }
  if(result)break;
  result=frame_clear_pending_actions(g_actor_choice_categories[((struct FrameActorObject *)object)->actor_id]);
  if(result==1)((struct FrameActorObject *)object)->reset=1;
  if(((struct FrameActorObject *)object)->reset==0)frame_actor_show_action_failure(object);
  if(((struct FrameActorObject *)object)->subtype==4) {
   if(!frame_find_objects(5,50,&target,1)) {
    transition_object_set_state(object,43);
    frame_set_variant_state(object,0);
   } else {
    frame_point_to_integer(&target->position,&point);
    result=frame_begin_actor_route(object,&target->position,&((struct FrameActorStateWork *)object)->movement_status,0,0);
    if(result==1)frame_set_variant_state(object,71);
    else {transition_object_set_state(object,43);frame_set_variant_state(object,0);}
   }
  } else {
   frame_add_game_value(-g_actor_choice_penalties[((struct FrameActorChoiceGame *)&g_resource_game_state)->stage][((struct FrameActorObject *)object)->actor_id]);
   audio_play_animation_cue(5);
   transition_object_set_state(object,34);
   frame_set_variant_state(object,0);
  }
  break;
 case 7:frame_set_variant_state(object,2);break;
 case 71:
  {unsigned int status=((struct FrameActorStateWork *)object)->movement_status;
   if(status==2)break;
   if(status==3||status==1) {frame_cancel_actor_route(object);transition_object_set_state(object,43);frame_set_variant_state(object,0);}
  }
  break;
 }
}
asm(".align 2, 0");
