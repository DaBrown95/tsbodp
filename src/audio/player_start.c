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

void audio_player_start(const struct AudioPlayerModule *m, int mode, int song) {
    if (mode & 4) {
        if (g_audio_player.state == 0)mode&=~4;
        else if (!(g_audio_player.flags & 4)) {
            audio_mark_channels(0, 4);
            display_text_copy_bytes(g_audio_player_backup, &g_audio_player, 1972);
        }
        else audio_player_stop_inline();
    }
    else {
        if (g_audio_player.flags & 4) {
            audio_stop_marked_channels(2);
            audio_stop_marked_channels(4);
        }
        audio_player_stop_inline();
    }
    g_audio_player.flags = mode;
    g_audio_player.song = (const unsigned char*)m;
    g_audio_player.tick = g_audio_player.speed = m->speed;
    g_audio_player.volume = 64;
    g_audio_player.volume_slide = 0;
    audio_player_set_volume_inline(g_audio_player_volume_current);
    audio_player_set_tempo_inline(AUDIO_CURRENT_MODULE->tempo);
    if (song >= 64)song = 0;
    g_audio_player.order = g_audio_player.restart_order = AUDIO_CURRENT_MODULE->song_index[song];
    if (!(g_audio_player.flags & 2))g_audio_player.restart_order = AUDIO_CURRENT_MODULE->restart;
    g_audio_player.row = 0;
    audio_player_load_row();
    g_audio_player.pending_order = g_audio_player.pending_row = -1;
    g_audio_player.loop_order = g_audio_player.loop_count = g_audio_player.loop_active = 0;
    g_audio_player.instrument_based = AUDIO_CURRENT_MODULE->instrument_based;
    g_audio_player.fast_volume_slides = AUDIO_CURRENT_MODULE->fast_slides;
    if (g_audio_player.instrument_based)g_audio_player.vibrato_offset = 32;
    else g_audio_player.vibrato_offset = 0;
    if (AUDIO_CURRENT_MODULE->linear_slides) {
        g_audio_player.calc_period = audio_period_linear;
        g_audio_player.calc_final_frequency = audio_frequency_linear;
    }
    else {
        g_audio_player.calc_period = audio_period_amiga;
        g_audio_player.calc_final_frequency = audio_frequency_amiga;
    }
    audio_zero_bytes(g_audio_player.tracks, 1920);
    {
        int i;
        for (i = 0; i<AUDIO_CURRENT_MODULE->channels; i++) {
            g_audio_player.tracks[i].vibrpos = g_audio_player.vibrato_offset;
            g_audio_player.tracks[i].vibrretrig = 1;
            g_audio_player.tracks[i].vibrtable = g_audio_sine;
            g_audio_player.tracks[i].tremretrig = 1;
            g_audio_player.tracks[i].tremtable = g_audio_sine;
            g_audio_player.tracks[i].panbretrig = 0;
            g_audio_player.tracks[i].panbtable = g_audio_sine;
            g_audio_player.tracks[i].sample = 0;
            g_audio_player.tracks[i].instrument = 0;
            g_audio_player.tracks[i].panning = AUDIO_CURRENT_MODULE->channel_pan[i];
            g_audio_player.tracks[i].i_vol = 64;
            g_audio_player.tracks[i].i_pan = 0;
            g_audio_player.tracks[i].cvolume = 64;
        }
    }
    g_audio_player.state = 2;
    audio_set_tick_callback(audio_player_tick);
}
