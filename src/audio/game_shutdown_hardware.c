#include "audio_game_initialize.h"

void audio_game_shutdown_hardware(void)
{
    audio_deactivate_hardware();
}
asm(".align 2, 0");
