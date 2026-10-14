#include "scene_audio_options.h"
void scene_audio_options_step(void) {
 unsigned int pressed=g_input_local_pressed[g_input_config.local_player];
 if(pressed&1)scene_audio_options_choose();
 else if(pressed&0xc0)scene_audio_options_change_row();
 else if(pressed&0x30)scene_audio_options_change_level();
 else {unsigned int cancel=2;cancel&=pressed;if(cancel){if(g_scene_audio_option_return_kind==5)scene_submit_default_request(5);else scene_submit_default_request(11);}}
}
asm(".align 2,0");
