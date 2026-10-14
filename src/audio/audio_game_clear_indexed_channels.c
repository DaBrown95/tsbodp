#include "scene_audio_options.h"
void audio_game_clear_indexed_channels(void){if(g_audio_game_options.samples_volume)audio_clear_indexed_channels();}
asm(".align 2,0");
