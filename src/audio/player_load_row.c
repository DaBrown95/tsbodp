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

void audio_player_load_row(void) {
    int row = g_audio_player.row;
    g_audio_player.pattern = ((const struct AudioPlayerModule *)g_audio_player.song)->patterns[((const struct AudioPlayerModule *)g_audio_player.song)->orders[g_audio_player.order]];
    if (!row) g_audio_player.stream = g_audio_player.pattern->data;
    else {
        g_audio_player.stream = &g_audio_player.pattern->data[g_audio_player.pattern->index[(row >> 2) & 15]];
        int l = row & 3;
        while (l) {
            unsigned char follow = *g_audio_player.stream++;
            if (!follow) {
                l--;
                continue;
            }
            if (follow & 32)g_audio_player.stream+=2;
            if (follow & 64)g_audio_player.stream++;
            if (follow & 128)g_audio_player.stream+=2;
        }
    }
}
