#include "scene_audio_options.h"
void scene_audio_options_choose(void) {
 unsigned int cue=0;
 switch(g_scene_request.parameter){
 case 0:case 1:break;
 case 2:resource_submit_scene(12,0,g_scene_audio_option_return_kind);break;
 case 3:resource_submit_scene(13,0,g_scene_audio_option_return_kind);cue=1;break;
 }
 if(cue){audio_game_stop_sample(g_scene_audio_option_cue);g_scene_audio_option_cue=audio_play_animation_cue(1);}
}
asm(".align 2,0");
