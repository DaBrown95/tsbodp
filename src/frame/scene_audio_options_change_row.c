#include "scene_audio_options.h"
void scene_audio_options_change_row(void) {
 unsigned int previous=g_scene_request.parameter;
 g_scene_request.parameter=input_step_local_vertical_pressed(&g_scene_request.parameter,0,3,1,g_input_config.local_player);
 scene_audio_options_draw_row(previous);
 scene_audio_options_draw_row(g_scene_request.parameter);
 audio_game_stop_sample(g_scene_audio_option_cue);
 g_scene_audio_option_cue=audio_play_animation_cue(2);
 {unsigned int row=g_scene_request.parameter;int x=64<<16;if(row<=1)x=40<<16;frame_set_position(g_display_scene_frame_objects[0],x,(row<<20)+(81<<16));}
}
asm(".align 2,0");
