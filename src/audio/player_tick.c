/*
 * Adapted from Krawall's timerRoutine in lib/player.c.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: game state fields and addresses, channel-volume refresh,
 * and a zero second argument for the fade completion notification.
 * Verified at the original ROM entry.
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

void audio_player_tick(void)
{
    if (++g_audio_player.tick >= g_audio_player.speed) {
        g_audio_player.tick = 0;
        audio_player_process_row();
    } else {
        audio_player_process_between_row();
    }
    if (g_audio_player.instrument_based)
        audio_player_process_instruments(&g_audio_player.tracks[0],
                                         g_audio_player.song[0]);
    if (g_audio_player_volume_step) {
        g_audio_player_volume_current += g_audio_player_volume_step;
        audio_set_global_volume(g_audio_player_volume_current *
            (g_audio_player.song ?
                g_audio_player.song[0x163] * g_audio_player.volume : 128 * 64) >> 13);
        audio_update_channel_volumes();
        if (g_audio_player_volume_current == g_audio_player_volume_target) {
            g_audio_player_volume_step = 0;
            if (g_audio_player_callback)
                g_audio_player_callback(1, 0);
        }
    }
}
