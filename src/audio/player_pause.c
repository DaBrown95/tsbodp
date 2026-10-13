/*
 * Adapted from Krawall's krapPause in lib/player.c.
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

void audio_player_pause(int sfx)
{
    if (g_audio_player.state != 2) return;
    g_audio_player.state = 1;
    audio_mark_channels(sfx, 2 + ((g_audio_player.flags & 4) ? 1 : 0));
    audio_set_tick_callback(0);
}
