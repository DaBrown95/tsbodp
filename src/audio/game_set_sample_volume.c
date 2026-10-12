#include "audio_game.h"

extern void audio_mixer_set_sample_volume(unsigned int);
void audio_game_set_sample_volume(unsigned int volume)
{
 unsigned char value = volume;
 audio_mixer_set_sample_volume(value);
 g_audio_game_options.samples_volume = value;
}
