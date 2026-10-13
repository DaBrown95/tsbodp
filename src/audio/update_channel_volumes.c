#include "audio_sample.h"

void audio_update_channel_volumes(void)
{
    struct AudioSampleChannel *channel = g_audio_sample_channels;
    int count = 32;
    do {
        if (channel->active) {
            unsigned int volume = channel->volume * g_audio_sample_volume_table[channel->volume_table_index];
            channel->volume_left = (volume * (64 - channel->pan)) >> 13;
            channel->volume_right = (volume * (channel->pan + 64)) >> 13;
        }
        channel++;
    } while (--count);
}
