#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "resource_view_effects.h"
#include "input.h"
#include "audio_game.h"
#include "frame_actor_speed_control.h"
void frame_disable_object_flags(struct FrameObject *,unsigned int);
void frame_actor_state_27(struct FrameObject *object)
{
 unsigned char player=((struct FrameActorObject *)object)->unknown_13;
 if(g_resource_view_effects[player].mode==1)frame_set_variant_state(object,2);
 switch(((struct FrameActorObject *)object)->variant_state) {
 case 0:
  frame_request_animation((struct FrameCommandObject *)object,86);
  frame_set_variant_state(object,2);
  frame_set_part_order(object,2,3);
  if(((struct FrameActorSpeedGame *)&g_resource_game_state)->resume)g_frame_actor_control_mode=1;
  else g_frame_actor_control_mode=0;
  if(!(object->flags&0x20000000)) {object->flags|=0x20000000;((struct FrameActorObject *)object)->direction*=2;}
  if(g_frame_actor_control_mode==0) {g_frame_actor_turn_timer=0;g_frame_actor_controlled_speed=0;}
  else {frame_set_variant_state(object,3);frame_actor_set_speed_cue(g_frame_actor_speed_cue_mode);((struct FrameActorSpeedGame *)&g_resource_game_state)->resume=0;}
  {struct FrameTransientEffect **slot=&g_frame_actor_speed_effect;*slot=frame_create_transient_effect(2,0,2);}
  if(g_frame_actor_speed_effect) {
   g_frame_actor_speed_effect->owner=object;
   g_frame_actor_speed_effect->phase=3;
   g_frame_actor_speed_effect->flags|=0x31180;
   g_frame_actor_speed_effect->width=8;
   g_frame_actor_speed_effect->height=20;
   g_frame_actor_speed_effect->enabled=1;
   g_frame_actor_speed_effect->unknown34=0;
   g_frame_actor_speed_effect->direction=g_actor_reverse_directions[((struct FrameActorObject *)object)->direction>>1];
   g_frame_actor_speed_effect->rate=0x10000;
   g_frame_actor_speed_effect->unknown43=0;
   g_frame_actor_speed_effect->mode=2;
  }
  g_frame_actor_speed_cue_mode=4;
  g_frame_actor_speed_frames=0;
  break;
 case 1:frame_request_animation((struct FrameCommandObject *)object,1);break;
 case 2:
  g_frame_actor_controlled_speed=0;
  if(g_resource_view_effects[player].mode!=1) {
   /* Keep this input argument live in its ABI register. */
   register unsigned char argument asm("r0")=player;
   unsigned char direction=input_rotate_direction(argument,((struct FrameActorObject *)object)->direction);
   if(direction!=16)frame_set_actor_turn_direction(object,direction);
   frame_set_variant_state(object,3);
  }
  break;
 case 3:
  if((g_input_current[g_frame_actor_need_input.local_player]&2)&&((struct FrameActorSpeedGame *)&g_resource_game_state)->resume==0) {
   struct FrameObject *actor=frame_create_speed_exit_actor(((struct FrameActorObject *)object)->direction>>1,object->position.x,object->position.y);
   if(!actor)return;
   transition_object_set_state(object,16);
   frame_set_variant_state(object,2);
   frame_set_part_order(object,2,6);
   frame_disable_object_flags(object,0x20000000);
   frame_set_actor_direction(object,((struct FrameActorObject *)object)->direction>>1);
   frame_request_animation((struct FrameCommandObject *)object,1);
   ((struct FrameActorSpeedGame *)&g_resource_game_state)->exit_flag=0;
   g_frame_actor_turn_ready=0;
   if(g_frame_actor_speed_effect)frame_destroy_transient_effect(g_frame_actor_speed_effect);
   ((struct FrameActorNeedState *)((struct FrameActorObject *)object)->actor_state)->countdown=450;
   ((struct FrameActorSpeedGame *)&g_resource_game_state)->world=g_frame_world_id;
   ((struct FrameActorSpeedGame *)&g_resource_game_state)->saved_position=object->position;
   audio_game_stop_sample(g_frame_actor_speed_cue_handle);
   frame_update_actor_state(actor);
   *(struct FrameActorSpeedBounds *)((char *)actor+0x98)=*(struct FrameActorSpeedBounds *)((char *)object+0x98);
  } else {
   /* Keep this input argument live in its ABI register. */
   register unsigned char argument asm("r0")=player;
   unsigned char direction=input_rotate_direction(argument,((struct FrameActorObject *)object)->direction);
   if(direction!=16) {
    if(g_input_current[g_frame_actor_need_input.local_player]&1) {
     if(--g_frame_actor_turn_timer==255) {
      frame_set_actor_turn_direction(object,direction);
      if(g_frame_actor_controlled_speed<=0x10000&&g_frame_actor_turn_ready==1) {g_frame_actor_turn_timer=1;g_frame_actor_controlled_speed=1;}
      else g_frame_actor_turn_timer=(unsigned char)(((g_frame_actor_controlled_speed/2)>>16)*0.4-2.0);
     }
     if(g_frame_actor_controlled_speed==0x80000&&g_frame_actor_restart_ready) {
      if(!audio_game_sample_active(g_frame_actor_restart_cue)&&g_frame_actor_speed_frames>11) {g_frame_actor_restart_cue=audio_play_animation_cue(72);g_frame_actor_restart_ready=0;}
     }
     g_frame_actor_speed_frames++;
    } else g_frame_actor_turn_ready=1;
   } else {g_frame_actor_restart_ready=1;g_frame_actor_speed_frames=0;}
   {
    struct FramePoint velocity;
    frame_actor_acceleration_velocity(object,&velocity);
    object->velocity=velocity;
   }
   if(g_frame_actor_speed_effect) {
    g_frame_actor_speed_effect->direction=g_actor_reverse_directions[((struct FrameActorObject *)object)->direction>>1];
    if(g_frame_actor_controlled_speed<=0x3ffff)g_frame_actor_speed_effect->width=8;
    else g_frame_actor_speed_effect->width=5;
    if((unsigned char)(((struct FrameActorObject *)object)->direction-4)>8)g_frame_actor_speed_effect->flags|=0x4000;
    else g_frame_actor_speed_effect->flags|=0x100;
   }
  }
  break;
 case 7:frame_set_variant_state(object,3);break;
 case 4:case 5:case 6:break;
 }
}
