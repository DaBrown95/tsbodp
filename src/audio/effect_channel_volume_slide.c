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
#include "audio_volume_effects.h"
void audio_effect_channel_volume_slide( struct AudioPlayerTrack *c, bool onrow )
{
    if( onrow ) {
        if( c->effectop )
            c->cvolslide = c->effectop;
    }
    else {
        u8 h = c->cvolslide >> 4;
        u8 l = c->cvolslide & 0xf;

        if( l ) {
            c->cvolume -= l;
            F_CLIP( c->cvolume, 0 );
            setChannelVol( c );
        }
        else if( h ) {
            c->cvolume += h;
            C_CLIP( c->cvolume, 0x40 );
            setChannelVol( c );
        }
    }
}
