/*
 * Adapted from Krawall's krapSetMusicVol in lib/player.c.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: game sequencer state and volume addresses, partial field views,
 * and tick/channel coordination calls; verified at the original ROM entry.
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
#include "audio_player.h"
#include "audio_sample.h"

void audio_player_set_volume(unsigned int volume, int fade)
{
    if (fade && g_audio_player.state == 2) {
        if (volume != g_audio_player_volume_current) {
            g_audio_player_volume_target = volume;
            g_audio_player_volume_step =
                g_audio_player_volume_target < g_audio_player_volume_current ? -1 : 1;
        }
    } else {
        g_audio_player_volume_step = 0;
        g_audio_player_volume_current = g_audio_player_volume_target = volume;
        audio_set_global_volume(g_audio_player_volume_current *
            (g_audio_player.song ?
                g_audio_player.song[0x163] * g_audio_player.volume : 128 * 64) >> 13);
        audio_update_channel_volumes();
    }
}
