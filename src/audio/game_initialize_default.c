#include "audio_game_initialize.h"

void audio_game_initialize_default(void)
{
    g_audio_control.pacing = 8;
    audio_game_initialize();
}
asm(".align 2, 0");
