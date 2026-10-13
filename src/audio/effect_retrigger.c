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
void audio_effect_retrigger( struct AudioPlayerTrack *c, bool onrow )
{
    if( onrow ) {
        if( c->effectop )
            c->retrig = c->effectop;

        if( !c->playnote && c->retrig ) {
            setChannelPosH( c, 0 );
        }
    }
    else {
        if( c->retrig && !quickModulo( g_audio_player.tick, c->retrig ) ) {
            setChannelPosH( c, 0 );
            u8 volchg = c->retrig >> 4;
            if( volchg ) {
                if( volchg >=1 && volchg <= 5 ) {
                    volDown( c, 1 << ( volchg - 1 ) );
                }
                else {
                    if( volchg >= 9 && volchg <= 0xd ) {
                        volUp( c, 1 << ( volchg - 9 ) );
                    }
                    else {
                        switch( volchg ) {
                        case 7:
                            volSet( c, c->volume >> 1 );
                            break;
                        case 0xf:
                            volSet( c, c->volume << 1 );
                            break;
                        case 0xe:
                            volSet( c, ( c->volume * 3 ) >> 1 );
                            break;
                        case 6:
                            // same as c->volume * 2/3 (exact as long as c->volume < 256)
                            volSet( c, ( 342 * c->volume ) >> 9 );
                            break;
                        }
                    }
                }
            }
        }
    }
}
