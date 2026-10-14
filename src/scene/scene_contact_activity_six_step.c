#include "scene_contact_activity_six.h"
#define STATE ((struct SceneContactActivitySixState *)g_scene_contact_state)
void scene_contact_activity_six_step(void) {
 if((g_audio_game_activity_notice.flags&4) && !(STATE->events&16)) {
  scene_contact_activity_six_create_first();
  scene_contact_activity_six_create_second(g_audio_game_activity_notice.parameter);
  g_audio_game_activity_notice.flags &= ~4;
 }
 if(STATE->events&1) {
  if(--STATE->palette_timer == -1) {
   display_create_palette_block(64,16,8,0,1,g_scene_contact_activity_six_reset_palette);
   STATE->events &= ~1;
  }
 }
 scene_contact_activity_six_check_pair();
 if(g_audio_game_activity_notice.flags&2)STATE->events |=16;
}
asm(".align 2,0");
