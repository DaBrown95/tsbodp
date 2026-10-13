/*
 * Adapted from Krawall lib/player_effects.h and lib/player.c.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: observed game track fields, earlier effect and note-start behavior with copied RAM mixer
 * handoffs. Ordinary C at original entries.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the GNU Lesser General Public License as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at your option) any later
 * version.
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See licenses/Krawall-LGPL-2.1.txt for the licence.
 */
#include "audio_table_effects.h"
void audio_effect_sample_offset( struct AudioPlayerTrack *c, bool onrow )
{
    if( c->effectop ) {
        if( !c->playnote )
            setChannelPosH( c, c->effectop );
        else
            c->pos = c->effectop;
    }
}
