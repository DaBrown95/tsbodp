#include "audio_sample.h"

void audio_configure_mix_mode(int mode)
{
    struct AudioSampleChannel *channel;
    unsigned int remaining;
    if (mode & 16) g_audio_sample_fade_enabled = 1;
    else g_audio_sample_fade_enabled = 0;
    mode &= 15;
    g_audio_sample_mix_mode = mode > 2 ? 0 : mode;
    channel = g_audio_sample_channels;
    remaining = 32;
    do {
        if (channel->active) {
            channel->mixing_mode = ((g_audio_sample_mix_mode == 2) ? 1 :
                channel->mixing_flags & g_audio_sample_mix_mode) << 3;
        }
        remaining--;
        channel++;
    } while (remaining);
}
