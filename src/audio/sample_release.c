#include "audio_sample.h"

unsigned int audio_sample_release(unsigned int handle)
{
    struct AudioSampleChannel *channel = &g_audio_sample_channels[(unsigned char)handle];
    if (channel->handle != handle) return 0;
    if (!g_audio_sample_fade_enabled) {
        channel->active = 0;
        return 1;
    }
    if (channel->active == 1) {
        if (channel->volume > 5) {
            unsigned int zero = 0;
            /* The playback table-index byte becomes the fade counter here. */
            channel->volume_table_index = 16;
            channel->fade_initial = *channel->cursor << 4;
            channel->fade_remaining = 128 - *channel->cursor;
            channel->unknown21 = 7;
            channel->cursor = channel->start;
            channel->step = zero;
            channel->mixing_mode = zero;
            channel->handle = zero;
            goto finished;
        }
    }
    channel->active = 0;
finished:
    return 1;
}
