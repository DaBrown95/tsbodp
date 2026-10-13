#include "audio_sample.h"

void audio_resume_channels(int state)
{
    struct AudioSampleChannel *channel = g_audio_sample_channels;
    int count = 32;
    do {
        if (channel->active == state) channel->active = 1;
        channel++;
    } while (--count);
}
