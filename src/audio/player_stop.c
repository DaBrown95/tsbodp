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

void audio_player_stop(void) {
    if ((&g_audio_player)->state == 0)return;
    (&g_audio_player)->state = 0;
    audio_set_tick_callback(0);
    int i;
    for (i = 0; i<(&g_audio_player)->song[0]; i++) {
        struct AudioPlayerTrack *track = &(&g_audio_player)->tracks[i];
        track->envelope_enabled = 0;
        audio_sample_release(track->handle);
    }
}
