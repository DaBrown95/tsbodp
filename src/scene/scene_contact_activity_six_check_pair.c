#include "scene_contact_activity_six.h"
#define STATE ((struct SceneContactActivitySixState *)g_scene_contact_state)
void scene_contact_activity_six_check_pair(void) {
 unsigned char correct_direction=0;
 struct FrameObject *first=STATE->first,*second;
 if(!first)return;
 second=STATE->second;
 if(!second)return;
 if(g_input_current[0]&0xf0){unsigned int direction_mask=0x10u<<first->unknown_0a;correct_direction=(g_input_current[0]&direction_mask)!=0;}
 {unsigned int button=g_input_pressed[0]&1;
 if(button||(g_input_pressed[0]&2)) {
  unsigned int mask=1<<second->unknown_0a;
 if((g_input_pressed[0]&mask) && correct_direction) {
   scene_contact_activity_six_set_channel_pair_volume(64);
   display_load_palette(g_scene_contact_activity_six_success_palette,64,16);
   frame_enable_object_flags(STATE->first,16);
   frame_enable_object_flags(STATE->second,16);
   ++STATE->amount;
   if(STATE->first->position.y>42*65536 && STATE->first->position.y<54*65536)
    scene_contact_add_activity_score(g_scene_contact_activity_six_options[STATE->option].reward*2);
   else scene_contact_add_activity_score(g_scene_contact_activity_six_options[STATE->option].reward);
  } else {
   audio_play_animation_cue(217);
   display_load_palette(g_scene_contact_activity_six_failure_palette,64,16);
   STATE->events|=2;
   scene_contact_activity_six_set_channel_pair_volume(0);
  }
  STATE->events|=1;STATE->palette_timer=6;
  ((struct FrameActorObject *)STATE->first)->actor_id=1;
  ((struct FrameActorObject *)STATE->second)->actor_id=1;
  STATE->first=0;STATE->second=0;
 }}
}
asm(".align 2,0");
