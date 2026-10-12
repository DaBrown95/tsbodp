#include "audio_game.h"
extern void vblank_audio_step(void);

void audio_sync_game_state(void)
{
    if (g_audio_control.flags & 0x40) vblank_audio_step();
    g_audio_control.flags &= 0x7f;
}
