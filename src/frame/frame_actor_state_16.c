#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "frame_actor_interaction.h"
#include "frame_actor_scene.h"
#include "resource_view_effects.h"
#include "resource_conditions.h"
#include "input.h"
#include "audio_game.h"
#include "frame_actor_idle.h"
struct FrameActorIdleNeedView {unsigned char unknown00[0xb0];struct FrameActorNeedState needs;};
void frame_actor_state_16(struct FrameObject *object)
{
 struct FramePoint velocity;
 unsigned int player=((struct FrameActorObject *)object)->unknown_13;
 unsigned int idle;
 unsigned char direction;
 if(g_resource_view_effects[player].mode==1)frame_set_variant_state(object,2);
 if(((struct FrameActorIdleGlobals *)&g_resource_game_state)->counter_addition_tick>4) {
  frame_add_actor_scene_counter_rate();
  ((struct FrameActorIdleGlobals *)&g_resource_game_state)->counter_addition_tick=0;
 }
 if(((struct FrameActorIdleGlobals *)&g_resource_game_state)->counter_reduction_tick>10) {
  ((struct FrameActorIdleGlobals *)&g_resource_game_state)->variant=1;
  frame_reduce_actor_scene_counter();
  g_actor_scene_request_active=0;
  transition_object_set_state(g_frame_actor_need_input.views[0].actor,38);
  ((struct FrameActorIdleGlobals *)&g_resource_game_state)->counter_reduction_tick=0;
 }
 if(((struct FrameActorIdleGlobals *)&g_resource_game_state)->timer==-1 && !((struct FrameActorIdleGlobals *)&g_resource_game_state)->variant) {
  g_scene_mode_bytes[0]=8;
  resource_submit_scene(1,0,12);
  ((struct FrameActorIdleGlobals *)&g_resource_game_state)->timer=-2;
 }
 switch(((struct FrameActorObject *)object)->variant_state) {
 case 1:frame_request_animation((struct FrameCommandObject *)object,1);break;
 case 2:
  idle=1;velocity.x=0;velocity.y=0;
  if(g_resource_view_effects[player].mode!=1) {
   direction=input_direction(player);
   if(direction!=8) {frame_set_actor_direction(object,input_direction(player));idle=0;}
   if(idle==0) {frame_actor_input_velocity(object,&velocity);frame_set_variant_state(object,3);}
   else frame_request_animation((struct FrameCommandObject *)object,1);
  } else frame_request_animation((struct FrameCommandObject *)object,1);
  object->velocity.x=velocity.x;object->velocity.y=velocity.y;
  break;
 case 3:
  idle=0;
  direction=input_direction(player);if(direction!=8)frame_set_actor_direction(object,direction);else idle=1;
  if(idle==0)frame_actor_input_velocity(object,&velocity);
  else {frame_set_variant_state(object,2);frame_request_animation((struct FrameCommandObject *)object,1);velocity.x=0;velocity.y=0;}
  object->velocity.x=velocity.x;object->velocity.y=velocity.y;
  break;
 case 5:
  {unsigned int flags=object->flags;
  if(flags&0x400000) {
   if(!(g_game_flags&0x20)) {resource_submit_scene(1,0,g_frame_world_id);object->flags&=~0x10u;}
   else object->flags=flags&~0x10u;
  }}
  break;
 case 7:
  if(--((struct FrameActorIdleWork *)object)->countdown==0xffff) {
   frame_set_variant_state(object,2);frame_request_animation((struct FrameCommandObject *)object,1);
   object->velocity.x=0;object->velocity.y=0;
  }
  break;
 case 74:
  frame_adjust_actor_needs((struct FrameActorNeedState *)&g_frame_actor_local_need_state,55,1);
  if(object->flags&0x400000) {frame_request_animation((struct FrameCommandObject *)object,1);frame_set_variant_state(object,2);}
  break;
 case 8:
  if(!(object->flags&0x20)) {
   object->flags|=0x20;
   ((struct FrameActorIdleWork *)object)->countdown=6;((struct FrameActorIdleWork *)object)->movement_units=15;
   object->velocity.x=0;object->velocity.y=0;
  } else if(--((struct FrameActorIdleWork *)object)->countdown==0xffff) {
   frame_set_variant_state(object,2);frame_request_animation((struct FrameCommandObject *)object,1);
  }
  break;
 case 23:
  if(object->flags&0x400000){frame_set_variant_state(object,2);frame_request_animation((struct FrameCommandObject *)object,1);}
  break;
 case 11:
  frame_request_animation((struct FrameCommandObject *)object,1);
  object->velocity.x=0;object->velocity.y=0;
  break;
 case 32:case 33:case 34:case 35:case 36:case 37:case 38:case 39:
  if(--((struct FrameActorIdleWork *)object)->countdown==0xffff) {frame_set_variant_state(object,2);frame_request_animation((struct FrameCommandObject *)object,1);}
  object->velocity.x=0;object->velocity.y=0;
  break;
 case 52:
 {unsigned int selected;
  frame_stop_motion(object);
  if(((struct FrameActorIdleNeedView *)&g_resource_game_state)->needs.values[5]==0x64000000) {
   selected=0;
   frame_request_animation((struct FrameCommandObject *)object,5);
   if(!frame_world_in_idle_exclusion_set(g_frame_world_id)&&g_frame_world_id!=6&&g_frame_world_id!=28&&g_frame_world_id!=37&&g_frame_world_id!=36&&(unsigned char)condition_group_complete(1,3)&&frame_random_range(1,100)<=50)selected=1;
   if(selected) {
    ((struct FrameActorIdleGlobals *)&g_resource_game_state)->variant=0;
    g_actor_scene_request_active=0;
    transition_object_set_state(g_frame_actor_need_input.views[0].actor,38);
   } else {
    if(((struct FrameActorCueOptions *)&g_resource_game_state)->variant==1)audio_play_animation_cue(121);
    else audio_play_animation_cue(122);
    frame_set_variant_state(object,23);
   }
  } else frame_adjust_actor_needs(&((struct FrameActorIdleNeedView *)&g_resource_game_state)->needs,44,1);
  object->velocity.x=0;object->velocity.y=0;
  break;}
 case 53:
  frame_stop_motion(object);
  if(((struct FrameActorIdleNeedView *)&g_resource_game_state)->needs.values[2]==0x64000000){frame_set_variant_state(object,2);frame_request_animation((struct FrameCommandObject *)object,1);}
  else {
   if(object->flags&0x400000)object->flags&=~0x400010u;
   frame_adjust_actor_needs(&((struct FrameActorIdleNeedView *)&g_resource_game_state)->needs,45,1);
   frame_set_actor_need_step_mode(1);
  }
  object->velocity.x=0;object->velocity.y=0;
  break;
 case 54:
  frame_stop_motion(object);
  if(object->flags&0x400000){frame_set_variant_state(object,2);frame_request_animation((struct FrameCommandObject *)object,1);}
  object->velocity.x=0;object->velocity.y=0;
  break;
 case 75:
  frame_stop_motion(object);
  if(--((struct FrameActorIdleWork *)object)->timer==-1 || (g_input_current[player]&2)) {
   if(!(g_input_current[player]&2))frame_cycle_idle_actor_palette();
   frame_set_variant_state(object,2);frame_request_animation((struct FrameCommandObject *)object,1);
  }
  break;
 }
}
