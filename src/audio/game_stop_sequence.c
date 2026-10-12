#include "audio_game.h"

extern void audio_player_stop(void);
void audio_game_stop_sequence(void)
{
 if(g_audio_game_options.sequences_volume) {
  audio_player_stop();
  g_audio_control.flags &= ~1;
 }
}
