#include "scene_contact_activity_seven.h"
void scene_contact_activity_seven_step_primary(struct FrameObject *base) {
 struct FrameActorObject *object=(void *)base;
 switch(object->variant_state) {
 case 0:
  if(g_input_pressed[0]&1) {
   frame_set_variant_state((struct FrameObject *)object,1);TIMER(object)=20;
   STATE->presses=1;
   frame_request_animation((struct FrameCommandObject *)object,1);
   frame_disable_object_flags((struct FrameObject *)object,16);
   STATE->score=(STATE->option+1)*2;
   if(!audio_game_sample_active(STATE->sample)) {
    if(GAME->gender==1)STATE->sample=audio_play_animation_cue(222);
    else STATE->sample=audio_play_animation_cue(224);
   }
  }
  break;
 case 1:
  if(--TIMER(object)==-1) {
   scene_contact_activity_seven_retreat((struct FrameObject *)object,9,10);
   if(object->variant_state==10) {
    scene_contact_add_activity_score(STATE->score);audio_select_sequence(47);
   }
  } else if(g_input_pressed[0]&1) {
   if(scene_contact_activity_seven_advance((struct FrameObject *)object,g_scene_contact_activity_seven_options[STATE->option].rounds[STATE->round].first,2,2)) {
    if(!audio_game_sample_active(STATE->sample)) {
     if(GAME->gender==1)STATE->sample=audio_play_animation_cue(223);
     else STATE->sample=audio_play_animation_cue(225);
    }
   }
  } else if(g_input_pressed[0]&128) {
   frame_set_variant_state((struct FrameObject *)object,9);frame_request_animation((struct FrameCommandObject *)object,6);
  }
  break;
 case 2:
  if(--TIMER(object)==-1)scene_contact_activity_seven_retreat((struct FrameObject *)object,6,9);
  else if(g_input_pressed[0]&1) {
   if(scene_contact_activity_seven_advance((struct FrameObject *)object,g_scene_contact_activity_seven_options[STATE->option].rounds[STATE->round].second,3,3)) {
    TIMER(object)=g_scene_contact_activity_seven_options[STATE->option].timer;
    scene_contact_activity_seven_create_effect(0);
   }
  } else if(g_input_pressed[0]&128) {
   frame_set_variant_state((struct FrameObject *)object,9);frame_request_animation((struct FrameCommandObject *)object,7);
  }
  break;
 case 3:
  if(--TIMER(object)==-1) {
   frame_set_variant_state((struct FrameObject *)object,9);frame_request_animation((struct FrameCommandObject *)object,7);
  } else if(g_input_pressed[0]&128) {
   frame_enable_object_flags((struct FrameObject *)object,16);frame_set_variant_state((struct FrameObject *)object,4);
   STATE->score+=(STATE->option+1)*3;
   if(!audio_game_sample_active(STATE->sample)) {
    if(GAME->gender==1)STATE->sample=audio_play_animation_cue(222);
    else STATE->sample=audio_play_animation_cue(224);
   }
  }
  break;
 case 4:
  if(scene_contact_activity_seven_finish_animation((struct FrameObject *)object,4,5)) {
   frame_disable_object_flags((struct FrameObject *)object,16);TIMER(object)=20;
   if(!audio_game_sample_active(STATE->sample)) {
    if(GAME->gender==1)STATE->sample=audio_play_animation_cue(223);
    else STATE->sample=audio_play_animation_cue(225);
   }
  }
  break;
 case 5:
  if(--TIMER(object)==-1)scene_contact_activity_seven_retreat((struct FrameObject *)object,8,9);
  else if(g_input_pressed[0]&1) {
   if(scene_contact_activity_seven_advance((struct FrameObject *)object,g_scene_contact_activity_seven_options[STATE->option].rounds[STATE->round].third,4,6)) {
    TIMER(object)=g_scene_contact_activity_seven_options[STATE->option].timer;
    scene_contact_activity_seven_create_effect(1);
   }
  } else if(g_input_pressed[0]&64) {
   frame_set_variant_state((struct FrameObject *)object,9);frame_request_animation((struct FrameCommandObject *)object,8);
  }
  break;
 case 6:
  if(--TIMER(object)==-1) {
   frame_set_variant_state((struct FrameObject *)object,9);frame_request_animation((struct FrameCommandObject *)object,8);
  } else if(g_input_pressed[0]&64) {
   TIMER(object)=30;frame_set_variant_state((struct FrameObject *)object,7);
   STATE->score+=g_scene_contact_activity_seven_options[STATE->option].rounds[STATE->round].reward;
   audio_select_sequence(46);
  }
  break;
 case 7:
  if(--TIMER(object)==-1) {
   frame_set_variant_state((struct FrameObject *)object,8);frame_request_animation((struct FrameCommandObject *)object,5);
   scene_contact_add_activity_score(STATE->score);
  }
  break;
 case 8:
  if(scene_contact_activity_seven_finish_animation((struct FrameObject *)object,0,0)) {
   if(++STATE->round>3) {
    STATE->flags|=1;frame_disable_object_flags((struct FrameObject *)object,16);
   } else scene_contact_activity_seven_draw_status();
  }
  break;
 case 9:
  if(scene_contact_activity_seven_finish_animation((struct FrameObject *)object,9,10)) {
   scene_contact_add_activity_score(STATE->score);audio_select_sequence(47);
  }
  break;
 case 10:
  if(scene_contact_activity_seven_finish_animation((struct FrameObject *)object,0,0)) {
   STATE->failures++;
   frame_set_animation_frame((struct FrameTickObject *)STATE->status,STATE->failures);
   if(STATE->failures>2) {
    STATE->flags|=1;frame_disable_object_flags((struct FrameObject *)object,16);
   }
  }
  break;
 }
 if((object->pending_updates&22)&&(object->pending_updates&20))
  frame_set_animation_variant((struct FrameObject *)object,object->requested_animation,g_frame_actor_direction_variants_signed[object->direction]);
 object->pending_updates=0;
 if((STATE->flags&1)&&object->actor_id==0) {
  register int bonus asm("r1")=STATE->failures;
  bonus=3-bonus;
  bonus*=STATE->option+1;
  bonus*=10;
  scene_contact_add_activity_score(bonus);
  object->actor_id=1;
 }
}
