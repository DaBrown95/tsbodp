#include "audio_game.h"
extern void audio_stop_sample(unsigned int);
void audio_game_stop_sample(unsigned int handle)
{
 if(g_audio_game_options.samples_volume) audio_stop_sample(handle);
}
