/*
 * Adapted from Krawall's kramSetPan in lib/mixer.arm.c.
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

int audio_set_channel_pan(unsigned int handle, int pan)
{
    struct AudioSampleChannel *channel = &g_audio_sample_channels[handle & 255];
    if (channel->handle != handle) return 0;
    if (g_audio_hardware_enabled) {
        channel->mix_function = pan == 0 ? 0 : (pan > 0 ? (pan >> 6) + 2 : (-pan) >> 6);
        channel->pan = pan;
    } else {
        channel->mix_function = 1;
        channel->pan = -64;
    }
    {
        unsigned int v = channel->volume * g_audio_sample_volume_table[channel->volume_table_index];
        channel->volume_left = (v * (64 - channel->pan)) >> 13;
        channel->volume_right = (v * (64 + channel->pan)) >> 13;
    }
    return 1;
}
