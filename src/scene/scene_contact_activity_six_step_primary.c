#include "scene_contact_activity_six.h"
#define STATE ((struct SceneContactActivitySixState *)g_scene_contact_state)
void scene_contact_activity_six_step_primary(struct FrameObject *base) {
 struct FrameActorObject *object=(void *)base;
 switch(object->variant_state) {
 case 0: {
  unsigned char events=STATE->events;
  unsigned short completed=(unsigned char)(events&16);
  if(completed) {
   completed=STATE->failures;
   if((unsigned short)completed<=1) {
    frame_request_animation((struct FrameCommandObject *)object,6);
    scene_contact_add_activity_score(40);
    if(STATE->failures==0)frame_request_animation((struct FrameCommandObject *)STATE->secondary,6);
    else frame_request_animation((struct FrameCommandObject *)STATE->secondary,5);
    audio_play_animation_cue(146);audio_play_animation_cue(220);
   } else if((unsigned short)completed<=g_scene_contact_activity_six_options[STATE->option].failure_threshold) {
    frame_request_animation((struct FrameCommandObject *)object,5);
    frame_request_animation((struct FrameCommandObject *)STATE->secondary,4);
    audio_play_animation_cue(130);audio_play_animation_cue(219);
   } else {
    frame_request_animation((struct FrameCommandObject *)object,4);audio_play_animation_cue(218);
   }
   frame_set_variant_state((struct FrameObject *)object,2);
   frame_set_variant_state(STATE->secondary,2);
  } else {
   unsigned char missed=events&2;
   if(missed) {
    register unsigned char cleared asm("r0")=STATE->events&0xf1;
    STATE->events=cleared;
    frame_request_animation((struct FrameCommandObject *)object,7);
    frame_set_variant_state((struct FrameObject *)object,1);
    STATE->amount=completed;
    ++STATE->failures;
   } else {
    int amount;
    const struct SceneContactActivitySixOption *incoming;
    const struct SceneContactActivitySixOption *option;
    register const struct SceneContactActivitySixOption *options asm("r9");
    amount=STATE->amount;
    incoming=g_scene_contact_activity_six_options;
    option=&incoming[STATE->option];
    options=incoming;
    if(amount>=option->first_threshold) {
     if(amount>=option->third_threshold) {
      frame_request_animation((struct FrameCommandObject *)object,3);
      STATE->events&=0xf1;STATE->amount=missed;
      audio_play_animation_cue(89);scene_contact_add_activity_score(30);
     } else {
      register unsigned char second_byte asm("r0")=events&8;
      register unsigned int second asm("r5")=second_byte;
      if(!second && amount>=option->second_threshold) {
       frame_request_animation((struct FrameCommandObject *)object,2);
       if(options[STATE->option].third_threshold==255) {
        STATE->events&=0xf1;STATE->amount=second;
       } else STATE->events|=8;
       audio_play_animation_cue(97);scene_contact_add_activity_score(20);
      } else {
       unsigned char first=STATE->events&4;
       if(!first && STATE->amount>=options[STATE->option].first_threshold) {
        frame_request_animation((struct FrameCommandObject *)object,1);
        if(options[STATE->option].second_threshold==255) {
         STATE->events&=0xf1;STATE->amount=first;
        } else STATE->events|=4;
        audio_play_animation_cue(132);scene_contact_add_activity_score(10);
       }
      }
     }
     frame_set_variant_state((struct FrameObject *)object,1);
    }
   }
  }
  break;
 }
 case 1:
  if(frame_object_has_flags((struct FrameObject *)object,0x400000)) {
   frame_request_animation((struct FrameCommandObject *)object,0);
   frame_set_variant_state((struct FrameObject *)object,0);
  }
  break;
 case 2:
  if(frame_object_has_flags((struct FrameObject *)object,0x400000)) {
   STATE->flags|=1;
   frame_set_variant_state((struct FrameObject *)object,3);
   frame_request_animation((struct FrameCommandObject *)object,0);
   frame_disable_object_flags((struct FrameObject *)object,16);
   audio_game_set_sequence_volume(STATE->saved_sequence_volume);
   audio_game_set_sample_volume(STATE->saved_sample_volume);
  }
  break;
 }
 if((object->pending_updates&0x16)&&(object->pending_updates&0x14))frame_set_animation_variant((struct FrameObject *)object,object->requested_animation,g_frame_actor_direction_variants_signed[object->direction]);
 object->pending_updates=0;
}
asm(".align 2,0");
