#include "audio_game.h"

extern void audio_player_set_volume(unsigned int,int);
void audio_game_set_sequence_volume(unsigned int volume)
{
 unsigned char value = volume;
 audio_player_set_volume(value,0);
 g_audio_game_options.sequences_volume = value;
}
