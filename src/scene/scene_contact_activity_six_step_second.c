#include "scene_contact_activity_six.h"
#define STATE ((struct SceneContactActivitySixState *)g_scene_contact_state)
void scene_contact_activity_six_step_second(struct FrameObject *base) {
 if(!STATE->second && !((struct FrameActorObject *)base)->actor_id && (unsigned int)base->position.y-25u*65536 <=48u*65536-1)
  STATE->second=base;
 if(STATE->second==base && base->position.y<25*65536) {
  STATE->second=0;
  audio_play_animation_cue(217);
  if(audio_game_get_channel_volume(0)!=0)audio_game_set_channel_volume(0,0);
  if(audio_game_get_channel_volume(1)!=0)audio_game_set_channel_volume(1,0);
  display_load_palette(g_scene_contact_activity_six_failure_palette,64,16);
  STATE->events|=1;STATE->palette_timer=6;STATE->events|=2;
 }
 scene_contact_activity_six_remove_finished(base);
}
asm(".align 2,0");
