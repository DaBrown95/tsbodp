#include "audio_game_initialize.h"

void audio_game_initialize(void)
{
    audio_initialize(1);
    audio_set_master_volume(0x40080);
    audio_configure_mix_mode(2);
    audio_game_set_pacing(g_audio_control.pacing);
    audio_game_set_sample_volume(g_audio_game_options.samples_volume);
    audio_game_set_sequence_volume(g_audio_game_options.sequences_volume);
    g_audio_control.sequence_id = 255;
    g_audio_control.flags = 0;
    audio_game_select_activity_callback(0);
}
asm(".align 2, 0");
