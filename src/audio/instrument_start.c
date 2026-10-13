/*
 * Adapted from Krawall lib/player.c and lib/mtypes.h.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: earlier standalone instrument lifecycle, contextual track handles
 * and copied ARM mixer transfers. Ordinary C at original entries.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the GNU Lesser General Public License as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at your option) any later
 * version.
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See licenses/Krawall-LGPL-2.1.txt for the licence.
 */
#include "audio_instrument_player.h"
AudioInstrumentHandle audio_instrument_start( const struct AudioInstrument *ins, int note, AudioInstrumentHandle old )
{
    struct AudioPlayerTrack* c = &g_audio_instrument_tracks[ old.channel ];

    if( c->instrument_id != old.val ) {
        c = &g_audio_instrument_tracks[ 0 ];
        int i = 0;

        while(c->envelope_enabled && i<6U){i++;c++;}
        if(i>=6U){
            c=&g_audio_instrument_tracks[0];i=0;
            while(audio_sample_active_ram(c->handle) && i<6U){i++;c++;}
            if(i>=6U)return (AudioInstrumentHandle){.val=0};
        }
        old.channel = i;
    }

    old.id = ++g_audio_instrument_generation;
    c->instrument_id = old.val;

    c->instrument = ins;
    c->sample = g_audio_player_samples[ ins->samples[ note ] ];
    c->volume = c->sample->volume;
    c->panning = c->sample->pan;
    c->period = c->periodc = calcPeriodLinear( note, c->sample );

    if( i_init( c ) )
        c->handle =	audio_start_sample_extended( c->sample, 1, c->handle, calcFinalFreqLinear( c->period ),	0, c->panning );
    else
        c->handle =	audio_start_sample_extended( c->sample, 1, c->handle, calcFinalFreqLinear( c->period ),	c->volume, c->panning );

    if( !c->handle ) {
        c->instrument_id = 0;
        return ( AudioInstrumentHandle ){ .val = 0 };
    }

    return old;
}
