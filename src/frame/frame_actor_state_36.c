#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "audio_game.h"
#include "frame_actor_social.h"
void frame_actor_state_36(struct FrameObject *object)
{
 struct FrameObject *actor=g_frame_actor_need_input.views[0].actor;
 unsigned int ready=0;
 if((unsigned int)frame_read_signed_parameter(g_frame_actor_social_probe,3)>5 && frame_actor_need_value(((struct FrameActorObject*)actor)->actor_state,2)>89) ready=1;
 switch(((struct FrameActorObject*)object)->variant_state) {
 case 2:
  frame_request_animation((struct FrameCommandObject*)object,1);
  frame_set_variant_state(object,7);
  ((struct FrameActorSocialWork*)object)->timer=120;
  frame_set_actor_direction(object,frame_direction_toward(object,actor));
  break;
 case 7:
  if(--((struct FrameActorSocialWork*)object)->timer==-1) {
   if(frame_random_chance(70)) {
    frame_request_animation((struct FrameCommandObject*)object,19);
    frame_set_variant_state(object,41);
    ((struct FrameActorSocialWork*)object)->timer=60;
    frame_set_actor_direction(object,frame_direction_toward(object,actor));
   } else {
    frame_request_animation((struct FrameCommandObject*)object,6);
    frame_set_variant_state(object,25);
    ((struct FrameActorSocialWork*)object)->timer=90;
    frame_set_actor_direction(object,frame_random_range(0,7));
   }
  }
  break;
 case 41:
  if(--((struct FrameActorSocialWork*)object)->timer==-1) frame_set_variant_state(object,2);
  break;
 case 25:
  if(--((struct FrameActorSocialWork*)object)->timer==-1) frame_set_variant_state(object,2);
  else {
   if(((struct FrameActorContactWork*)object)->contact) {
    frame_request_animation((struct FrameCommandObject*)object,1);
    frame_set_actor_direction(object,frame_direction_toward(object,actor));
    frame_set_variant_state(object,7);
    ((struct FrameActorSocialWork*)object)->timer=30;
   }
   frame_actor_refresh_terrain(object);
  }
  break;
 case 4:
  frame_set_actor_direction(object,frame_direction_toward(object,actor));
  frame_stop_motion(object);
  frame_set_actor_direction(actor,frame_direction_toward(actor,object));
  frame_stop_motion(actor);
  if(ready) {
   frame_request_animation((struct FrameCommandObject*)object,1);
   transition_object_set_state(actor,0);
   frame_request_animation((struct FrameCommandObject*)actor,40);
   frame_set_variant_state(object,8);
  } else {
   frame_stop_motion(object);
   frame_stop_motion(actor);
   transition_object_set_state(actor,0);
   frame_request_animation((struct FrameCommandObject*)object,40);
   frame_set_variant_state(object,44);
  }
  break;
 case 8:
  if(actor->flags&0x400000) {
   transition_object_set_state(actor,16);
   frame_set_variant_state(actor,2);
   frame_request_animation((struct FrameCommandObject*)actor,1);
   frame_request_animation((struct FrameCommandObject*)object,42);
   frame_set_variant_state(object,42);
   ((struct FrameActorSocialWork*)object)->timer=34;
   audio_play_animation_cue(228);
  }
  break;
 case 44:
  if(object->flags&0x400000) {
   frame_request_animation((struct FrameCommandObject*)object,1);
   frame_set_variant_state(object,11);
   frame_request_animation((struct FrameCommandObject*)actor,43);
   audio_play_animation_cue(228);
  }
  break;
 case 11:
  if(actor->flags&0x400000) {
   frame_clear_animation_pending(actor);
   frame_set_actor_direction(object,4);
   frame_request_animation((struct FrameCommandObject*)object,19);
   frame_set_variant_state(object,43);
   ((struct FrameActorSocialWork*)object)->timer=120;
   ((struct FrameActorSocialWork*)object)->cue_timer=0;
   ((struct FrameActorSocialWork*)object)->cue_count=0;
   audio_play_animation_cue(229);
  }
  break;
 case 42:
  if(--((struct FrameActorSocialWork*)object)->timer==-1) audio_play_animation_cue(229);
  if(object->flags&0x400000) {
   frame_clear_animation_pending(object);
   frame_set_variant_state(object,43);
   resource_set_triple(3,4,2);
   ((struct FrameActorSocialWork*)object)->cue_timer=0;
   ((struct FrameActorSocialWork*)object)->cue_count=0;
  }
  break;
 case 43:
  if(((struct FrameActorSocialWork*)object)->cue_count<=2 && ++((struct FrameActorSocialWork*)object)->cue_timer==11) {
   ((struct FrameActorSocialWork*)object)->cue_count++;
   ((struct FrameActorSocialWork*)object)->cue_timer=0;
   audio_play_animation_cue(227);
  }
  if(ready!=1 && --((struct FrameActorSocialWork*)object)->timer==-1) transition_object_set_state(actor,37);
  break;
 case 3:
 case 5:
 case 6:
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
 case 40:break;
 }
}
asm(".align 2, 0");
