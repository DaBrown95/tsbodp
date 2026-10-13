/*
 * Adapted from Krawall's kramPlayExt in lib/mixer.arm.c.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: game sample/channel layout, observed mixer indices and mono pan,
 * and fixed-step playback parameters; verified at the RAM execution address.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the GNU Lesser General Public License as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at your option) any later
 * version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See licenses/Krawall-LGPL-2.1.txt for the licence.
 */
#include "audio_playback.h"

#define SETQUALITY { \
    unsigned int quality = ((g_audio_sample_mix_mode == 2) ? 1 : \
        g_audio_sample_mix_mode & chn->mixing_flags) << 3; \
    chn->mixing_mode = quality; \
}
#define SETPANNING(x) if (g_audio_hardware_enabled) { \
    chn->mix_function = (x == 0) ? 0 : ((x) > 0 ? ((x) >> 6) + 2 : (-x) >> 6); \
    chn->pan = x; \
} else { \
    chn->mix_function = 1; \
    chn->pan = -64; \
}
#define SETVOLUME(x) chn->volume = x
#define SETFREQUENCY(x) if (chn->step >= 0) chn->step = (x) << 2; else chn->step = -((x) << 2)
#define SETLRVOLUME { \
    unsigned int v = chn->volume * g_audio_sample_volume_table[chn->volume_table_index]; \
    chn->volume_left = (v * (64 - chn->pan)) >> 13; \
    chn->volume_right = (v * (64 + chn->pan)) >> 13; \
}

/* The reference inlines the separately reconstructed release operation. */
static __inline__ unsigned int release_handle(unsigned int handle)
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
            channel->tail.fade.initial = *channel->cursor << 4;
            channel->tail.fade.remaining = 128 - *channel->cursor;
            channel->mix_function = 7;
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
unsigned int audio_start_sample_extended(const struct AudioSample *s, int sfx,
    unsigned int handle, unsigned int freq, unsigned int vol, int pan)
{
    register unsigned int channel_index __asm__("r4") = (unsigned char)handle;
    struct AudioSampleChannel *chn = &g_audio_sample_channels[channel_index];

    if (g_audio_sample_fade_enabled)
        release_handle(handle);

    if (chn->handle != handle) {
        register int i __asm__("r1") = 0;
        chn = &g_audio_sample_channels[0];
        while (chn->active && i < 32) {
            i++;
            chn++;
        }
        if (i >= 32) return 0;
        {
            /* Remember the selected low-byte handle before its new generation. */
            unsigned int selected = (unsigned char)i;
            channel_index = selected;
            handle = selected;
        }
    }

    handle = channel_index | (++g_audio_channel_counter << 8);
    chn->volume_table_index = sfx & 1;
    chn->handle = handle;
    SETQUALITY;
    SETPANNING(pan);
    SETVOLUME(vol);
    chn->step = 0;
    SETFREQUENCY(freq);
    SETLRVOLUME;

    chn->mixing_flags = s->mixing_flags;
    chn->cursor = chn->start = s->data;
    chn->loop_length = s->loop_length;
    chn->end = s->end;
    chn->loop_mode = s->loop_mode;
    chn->fraction = 0;
    chn->tail.loop_start = chn->end - chn->loop_length;
    chn->active = 1;
    return handle;
}
