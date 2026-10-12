#include "audio_game.h"

unsigned int audio_play_animation_cue(unsigned int id)
{
    unsigned int handle = 0;
    if (g_audio_game_options.samples_enabled) {
        struct AudioCueDescriptor *table = g_audio_cue_descriptors;
        struct AudioCueDescriptor *cue = (struct AudioCueDescriptor *)((id << 2) + (unsigned int)table);
        switch (cue->kind) {
        case 1:
            g_audio_control.flags |= 0x80;
            handle = audio_play_sample(g_audio_samples[g_audio_sample_parameters[cue->sample_id].sample_id], 1, 0);
            audio_set_sample_pitch(handle, g_audio_sample_parameters[cue->sample_id].pitch);
            audio_sync_game_state();
        break;
        case 2: {
            unsigned char variant = (unsigned char)game_random_inclusive(7);
            if (g_audio_sample_variants[cue->sample_id][variant].sample_id != 255) {
                g_audio_control.flags |= 0x80;
                handle = audio_play_sample(g_audio_samples[g_audio_sample_variants[cue->sample_id][variant].sample_id], 1, 0);
                audio_set_sample_pitch(handle, g_audio_sample_variants[cue->sample_id][variant].pitch);
                audio_sync_game_state();
            }
        }
        }
    }
    return handle;
}
