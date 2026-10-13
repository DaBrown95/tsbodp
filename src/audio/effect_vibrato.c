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
#include "audio_pitch_effects.h"
void audio_effect_vibrato( struct AudioPlayerTrack *c, bool onrow )
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
