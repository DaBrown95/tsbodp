/*
 * Adapted from Krawall's processInbetweenRow in lib/player.c.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: observed game track fields and addresses, and semantic effect tables.
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

void audio_player_process_between_row(void)
{
    struct AudioPlayerTrack *c = g_audio_player.tracks;
    int i;
    for (i = g_audio_player.song[0]; i; i--, c++) {
        if (c->volume_effect) {
            if (g_audio_volume_effects[c->volume_effect >> 4].update_enabled)
                g_audio_volume_effects[c->volume_effect >> 4].apply(c, 0);
        }
        if (c->effect) {
            if (g_audio_track_effects[c->effect].update_enabled)
                g_audio_track_effects[c->effect].apply(c, 0);
            if (g_audio_track_effects[c->effect].tick)
                g_audio_track_effects[c->effect].tick(c, 0);
        }
    }
}
