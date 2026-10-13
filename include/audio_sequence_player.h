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
#ifndef AUDIO_SEQUENCE_PLAYER_H
#define AUDIO_SEQUENCE_PLAYER_H
#include "audio_player.h"

/* The game stores a byte row count, so pattern data starts at offset 0x21. */
struct AudioPattern {
    unsigned short index[16];
    unsigned char rows, data[1];
};
/* Partial module prefix; serialized pattern and track counts need valid input. */
struct AudioPlayerModule {
    unsigned char channels, numOrders, restart, orders[256];
    signed char channel_pan[32];
    unsigned char song_index[64], global_volume, speed, tempo;
    unsigned char instrument_based, linear_slides, fast_slides, unknown169[3];
    const struct AudioPattern *patterns[];
};
#define AUDIO_CURRENT_MODULE ((const struct AudioPlayerModule *)g_audio_player.song)

void audio_player_load_row(void);
void audio_player_advance_row(void);
void audio_player_stop(void);
void audio_player_finish_jingle(void);
void audio_player_start(const struct AudioPlayerModule *, int, int);
void audio_set_tick_bpm(int);
void audio_set_global_volume(unsigned int);
void audio_update_channel_volumes(void);
void audio_mark_channels(int, int);
void audio_resume_channels(int);
void audio_stop_marked_channels(int);
/* Accepted ARM routine copied to RAM; direct callers need an indirect transfer. */
unsigned int audio_sample_release(unsigned int) __attribute__((long_call));
void *display_text_copy_bytes(void *, const void *, unsigned int);
void audio_zero_bytes(void *, unsigned int);
extern unsigned char g_audio_player_backup[];
extern const short g_audio_sine[];
unsigned short audio_period_linear(unsigned int, const void *);
unsigned short audio_period_amiga(unsigned int, const void *);
unsigned int audio_frequency_linear(unsigned int);
unsigned int audio_frequency_amiga(unsigned int);

static inline void audio_player_stop_inline(void)
{
    int i;
    if (g_audio_player.state == 0) return;
    g_audio_player.state = 0;
    audio_set_tick_callback(0);
    for (i = 0; i < AUDIO_CURRENT_MODULE->channels; i++) {
        struct AudioPlayerTrack *c = &g_audio_player.tracks[i];
        c->envelope_enabled = 0;
        audio_sample_release(c->handle);
    }
}
static inline void audio_player_set_volume_inline(unsigned int vol)
{
    g_audio_player_volume_step = 0;
    g_audio_player_volume_current = g_audio_player_volume_target = vol;
    audio_set_global_volume(g_audio_player_volume_current *
        (g_audio_player.song ?
            AUDIO_CURRENT_MODULE->global_volume * g_audio_player.volume : 128 * 64) >> 13);
    audio_update_channel_volumes();
}
static inline void audio_player_set_tempo_inline(int tempo)
{
    g_audio_player.tempo = tempo;
    audio_set_tick_bpm(24 * tempo);
}
#endif
