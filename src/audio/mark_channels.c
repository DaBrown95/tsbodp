#include "audio_sample.h"

void audio_mark_channels(int all, int state)
{
    struct AudioSampleChannel *channel = g_audio_sample_channels;
    int count = 32;
    do {
        if (channel->active == 1) {
            if (all || !channel->volume_table_index)
                channel->active = state;
        }
        channel++;
    } while (--count);
}
