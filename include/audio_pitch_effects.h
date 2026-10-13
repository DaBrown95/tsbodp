/*
 * Adapted from Krawall lib/player_effects.h and lib/player.c.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: observed game track fields, signed periods and copied RAM sample-step
 * and release calls. Ordinary C at original entries.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the GNU Lesser General Public License as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at your option) any later
 * version.
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See licenses/Krawall-LGPL-2.1.txt for the licence.
 */
#ifndef AUDIO_PITCH_EFFECTS_H
#define AUDIO_PITCH_EFFECTS_H
#include "audio_player_decode.h"
#include "audio_pitch.h"
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed char s8;typedef int bool;
#define true 1
#define false 0
#define TABLE_VIBRATO_LENGTH 64
#define EFF_VOLSLIDE_VIBRATO 23
static inline void setChannelFreq(struct AudioPlayerTrack *c) { c->periodc=c->period;audio_set_sample_step(c->handle,g_audio_player.calc_final_frequency(c->period)); }
static inline void setChannelFreqH(struct AudioPlayerTrack *c,u32 p) { c->periodc=p;audio_set_sample_step(c->handle,g_audio_player.calc_final_frequency(p)); }
static inline void stopChannel(struct AudioPlayerTrack *c) { c->envelope_enabled=false;audio_sample_release(c->handle); }
static inline void audio_effect_vibrato_inline( struct AudioPlayerTrack *c, bool onrow )
{
    if( onrow ) {
        // retrig vibrato?
        if( c->playnote && c->vibrretrig )
            c->vibrpos = g_audio_player.vibrato_offset;

        // speed/depth seperately
        if( c->effectop & 0x0f )
            c->vibrdepth = ( c->effectop & 0xf ) << 2;
        if( c->effectop & 0xf0 )
            c->vibrspeed = c->effectop >> 4;

        // don't reset if last effect was volslide-vibrato
        if( c->resetnote && c->leffect == EFF_VOLSLIDE_VIBRATO )
            c->resetnote = false;
    }
    else {
        u16 vperiod = c->period + ( ( c->vibrdepth * c->vibrtable[ c->vibrpos ] ) >> 7 );
        setChannelFreqH( c, vperiod );
        c->vibrpos += c->vibrspeed;
        c->vibrpos &= ( TABLE_VIBRATO_LENGTH - 1 );
        c->resetnote = true;
    }
}

typedef short s16;
extern const short g_audio_random_wave[], g_audio_square_wave[], g_audio_ramp_wave[];
/* These earlier game helpers take explicit temporary modulation values. */
static inline int setChannelVolH(struct AudioPlayerTrack *c, u32 volume)
{
    return audio_set_channel_volume(c->handle,
        volume * c->cvolume * c->i_vol >> 6);
}
static inline int setChannelPanH(struct AudioPlayerTrack *c, int pan)
{
    s16 x = pan + c->i_pan;
    F_CLIP(x, -64);
    C_CLIP(x, 64);
    return audio_set_channel_pan(c->handle, x);
}
#endif
