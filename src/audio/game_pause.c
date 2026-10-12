#include "audio_game.h"

extern int audio_player_is_paused(void);
extern void audio_player_pause(int);
void audio_game_pause(void)
{
 if(g_audio_game_options.sequences_volume && !audio_player_is_paused()) {
  audio_player_pause(0);
  g_audio_control.flags |= 1;
 }
}
