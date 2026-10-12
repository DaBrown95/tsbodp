#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "audio_game.h"
void frame_enable_object_flags(struct FrameObject *,unsigned int);
void frame_disable_object_flags(struct FrameObject *,unsigned int);
void frame_actor_state_41(struct FrameObject *object)
{
 struct FrameObject *actor=g_frame_actor_need_input.views[0].actor;
 switch(((struct FrameActorObject *)object)->variant_state) {
 case 0:case 2:
  frame_enable_object_flags(object,1);
  frame_request_animation((struct FrameCommandObject *)object,93);
  frame_set_variant_state(object,49);
  frame_set_actor_direction(object,frame_direction_toward(object,actor));
  break;
 case 49:
  if(object->flags&0x400000) {
   frame_request_animation((struct FrameCommandObject *)object,1);
   frame_set_variant_state(object,7);
  }
  break;
 case 7:
  if(--((struct FrameActorStateWork *)object)->timer==-1) {
   if((object->flags&0x800000) && frame_begin_actor_route(object,&object->destination,&((struct FrameActorStateWork *)object)->movement_status,3,0)==1) {
    frame_request_animation((struct FrameCommandObject *)object,6);
    frame_set_variant_state(object,45);
   } else {
    frame_request_animation((struct FrameCommandObject *)object,6);
    frame_set_variant_state(object,25);
    ((struct FrameActorStateWork *)object)->timer=frame_random_range(30,90);
    frame_actor_choose_walk_direction(object);
   }
  } else frame_actor_state_46(object);
  break;
 case 25:
  if(--((struct FrameActorStateWork *)object)->timer==-1) {
   frame_set_variant_state(object,7);
   ((struct FrameActorStateWork *)object)->timer=frame_random_range(150,300);
   frame_actor_choose_walk_direction(object);
  } else {
   if(((struct FrameActorContactWork *)object)->contact) {
    frame_request_animation((struct FrameCommandObject *)object,1);
    frame_actor_choose_walk_direction(object);
    frame_set_variant_state(object,7);
    ((struct FrameActorStateWork *)object)->timer=30;
   }
   frame_actor_refresh_terrain(object);
  }
  break;
 case 64:
  frame_set_actor_direction(object,frame_direction_toward(object,actor));
  frame_stop_motion(object);
  frame_set_actor_direction(actor,frame_direction_toward(actor,object));
  frame_stop_motion(actor);
  if(((struct FrameActorCueOptions *)&g_resource_game_state)->variant==0)audio_play_animation_cue(131);
  else audio_play_animation_cue(130);
  if(((struct FrameActorObject *)object)->indicator) frame_disable_object_flags(((struct FrameActorObject *)object)->indicator,1);
  frame_request_animation((struct FrameCommandObject *)((struct FrameActorObject *)g_frame_actor_need_input.views[0].actor)->indicator,95);
  frame_set_variant_state(((struct FrameActorObject *)g_frame_actor_need_input.views[0].actor)->indicator,4);
  break;
 case 4:
  if(object->flags&0x400000) {
   frame_request_animation((struct FrameCommandObject *)object,94);
   transition_object_set_state(actor,0);
   frame_request_animation((struct FrameCommandObject *)actor,70);
   frame_set_variant_state(object,11);
  }
  break;
 case 11:
  if(actor->flags&0x400000) {
   frame_set_variant_state(object,43);
   frame_clear_animation_pending(actor);
   ((struct FrameActorStateWork *)object)->timer=30;
  }
  break;
 case 43:
  if(--((struct FrameActorStateWork *)object)->timer==-1) {
   transition_object_set_state(actor,47);
   frame_set_variant_state(actor,48);
   transition_object_set_state(object,1);
  }
  break;
 case 45:
  if(((struct FrameActorStateWork *)object)->movement_status==2)break;
  if(((struct FrameActorStateWork *)object)->movement_status==3) {
   frame_set_variant_state(object,25);
   frame_cancel_actor_route(object);
   ((struct FrameActorStateWork *)object)->timer=frame_random_range(30,90);
   frame_actor_choose_walk_direction(object);
  } else if(((struct FrameActorStateWork *)object)->movement_status==1) {
   frame_set_variant_state(object,50);
   frame_request_animation((struct FrameCommandObject *)object,94);
  }
  break;
 case 50:
  if(object->flags&0x400000)transition_object_set_state(object,1);
  break;
 case 1:
 case 3:
 case 5:
 case 6:
 case 8:
 case 9:
 case 10:
 case 12:
 case 13:
 case 14:
 case 15:
 case 16:
 case 17:
 case 18:
 case 19:
 case 20:
 case 21:
 case 22:
 case 23:
 case 24:
 case 26:
 case 27:
 case 28:
 case 29:
 case 30:
 case 31:
 case 32:
 case 33:
 case 34:
 case 35:
 case 36:
 case 37:
 case 38:
 case 39:
 case 40:
 case 41:
 case 42:
 case 44:
 case 46:
 case 47:
 case 48:
 case 51:
 case 52:
 case 53:
 case 54:
 case 55:
 case 56:
 case 57:
 case 58:
 case 59:
 case 60:
 case 61:
 case 62:
 case 63:
  break;
 }
}
asm(".align 2, 0");
