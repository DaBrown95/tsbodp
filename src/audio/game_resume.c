#include "audio_game.h"

extern void audio_player_resume(void);
void audio_game_resume(void)
{
 if(g_audio_game_options.sequences_volume && (g_audio_control.flags & 1)) {
  audio_player_resume();
  g_audio_control.flags &= ~1;
 }
}
