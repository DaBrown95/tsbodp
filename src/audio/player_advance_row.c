/*
 * Adapted from Krawall lib/player.c and lib/mtypes.h.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: observed game layouts, direct RAM mixer transfers and the earlier
 * order-jump, callback and channel-stop behavior. Ordinary C at original entries.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the GNU Lesser General Public License as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at your option) any later
 * version.
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See licenses/Krawall-LGPL-2.1.txt for the licence.
 */
#include "audio_sequence_player.h"

void audio_player_advance_row(void) {
    if (g_audio_player.pending_order >= 0) {
        g_audio_player.order = g_audio_player.pending_order<AUDIO_CURRENT_MODULE->numOrders?g_audio_player.pending_order:0;
        g_audio_player.pending_order = -1;
        g_audio_player.row = 0;
        audio_player_load_row();
    }
    else if (++g_audio_player.row >= g_audio_player.pattern->rows || g_audio_player.pending_row >= 0) {
        int marker = 0;
        while (AUDIO_CURRENT_MODULE->orders[++g_audio_player.order] == 254 && g_audio_player.order<AUDIO_CURRENT_MODULE->numOrders)marker = 1;
        if (marker && g_audio_player_callback)g_audio_player_callback(4, 0);
        if (g_audio_player.order >= AUDIO_CURRENT_MODULE->numOrders || (marker && (g_audio_player.flags & 2))) {
            g_audio_player.order = g_audio_player.restart_order;
            if (!(g_audio_player.flags & 1)) {
                if (g_audio_player.flags & 4) {
                    audio_player_finish_jingle();
                    return;
                }
                else {
                    if (g_audio_player_callback)g_audio_player_callback(2, 0);
                    audio_player_stop();
                    return;
                }
            }
            if (g_audio_player_callback)g_audio_player_callback(6, 0);
        }
        g_audio_player.row = 0;
        audio_player_load_row();
    }
    if (g_audio_player.pending_row >= 0) {
        g_audio_player.row = g_audio_player.pending_row<g_audio_player.pattern->rows?g_audio_player.pending_row:0;
        audio_player_load_row();
        g_audio_player.pending_row = -1;
    }
}
