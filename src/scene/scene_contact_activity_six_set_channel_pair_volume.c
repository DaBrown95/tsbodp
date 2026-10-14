#include "scene_contact_activity_six.h"
#define STATE ((struct SceneContactActivitySixState *)g_scene_contact_state)
void scene_contact_activity_six_set_channel_pair_volume(unsigned int value) {
 if(audio_game_get_channel_volume(0)!=value)audio_game_set_channel_volume(0,value);
 if(audio_game_get_channel_volume(1)!=value)audio_game_set_channel_volume(1,value);
}
asm(".align 2,0");
