#include "frame_option_object.h"

static inline struct ConditionActorEntries *frame_option_entries(void)
{
 register struct FrameOptionWorld *world asm("r0")=(struct FrameOptionWorld *)&g_resource_game_state;
 return world->entries;
}
void frame_option_action_step(struct FrameObject *base)
{
 struct FrameOptionObject *object=(struct FrameOptionObject *)base;
 unsigned char success=0;
 unsigned int finished;
 frame_stop_motion(object->target);
 finished=0;
 switch(object->variant) {
 case 0:
  g_actor_scene_result_id.id=0x17e1;
  ((struct FrameOptionRequest *)&g_actor_scene_request)->active=0;
  ((struct FrameOptionRequest *)&g_actor_scene_request)->reset1=0;
  ((struct FrameOptionRequest *)&g_actor_scene_request)->reset2=0;
  scene_submit_default_request(2);
  frame_set_variant_state((struct FrameObject *)object,55);
  break;
 case 55:
  if(((struct FrameOptionChoiceState *)&g_resource_scene_arg)->result!=-1) {
   if((unsigned char)actor_entry_has_space(frame_option_entries())) {
    frame_request_animation((struct FrameCommandObject *)object->target,32);
    frame_set_variant_state((struct FrameObject *)object,14);
    object->timer=8;
   } else goto failed;
  } else {
   frame_option_configure((struct FrameObject *)object);
   finished=1;
  }
  break;
 case 14:
  if(--object->timer!=-1)break;
  frame_set_variant_state((struct FrameObject *)object,15);
  if(object->subtype==1)success=(unsigned char)actor_entry_add(frame_option_entries(),125,object->option,0);
  else if(object->subtype==2)success=(unsigned char)actor_entry_add(frame_option_entries(),126,object->option,0);
  if(success==1) {
   if(object->subtype==1 && object->option<=7) {
    register unsigned char *flags asm("r0")=(unsigned char *)&g_resource_game_state;
    flags+=0xe5;
    *flags|=1u<<object->option;
   }
   frame_disable_object_flags((struct FrameObject *)object,1);
   audio_play_animation_cue(179);
  } else {
failed:
   frame_option_configure((struct FrameObject *)object);
   finished=1;
   g_scene_mode_flags.rows[g_input_config.local_player].flags|=0x200000;
  }
  break;
 case 15:
  if(object->target->flags&0x400000) {
   transition_object_set_state((struct TransitionObject *)object,1);
   frame_enable_object_flags((struct FrameObject *)object,2);
   finished=1;
  }
  break;
 }
 if(finished==1) {
  transition_object_set_state((struct TransitionObject *)object->target,16);
  frame_set_variant_state(object->target,2);
  frame_request_animation((struct FrameCommandObject *)object->target,1);
 }
}
asm(".align 2, 0");
