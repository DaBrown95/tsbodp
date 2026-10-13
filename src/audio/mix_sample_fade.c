/*
 * Adapted from Krawall lib/mixer.arm.c and lib/mixer_private.h.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: observed 44-byte backend fields, signed ramp accumulator view
 * and copied ARM bias handoff. Ordinary C at the original ARM entry.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the GNU Lesser General Public License as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at your option) any later
 * version.
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See licenses/Krawall-LGPL-2.1.txt for the licence.
 */
#include "audio_fade.h"
void audio_mix_sample_fade( struct AudioSampleChannel *c, short *dest, unsigned int amount )
{
    unsigned int smp = c->volume_table_index <= amount ? c->volume_table_index : amount;

    // sample order in buffer: L L L L R R R R
    for( ; smp; smp -= 4 ) {
        *( dest + 0 ) += ( c->volume_left * ( (short)c->tail.fade.initial >> 4 ) ) >> 3;
        *( dest + 4 ) += ( c->volume_right * ( (short)c->tail.fade.initial >> 4 ) ) >> 3;
        dest++;
        c->tail.fade.initial += c->tail.fade.remaining;
        *( dest + 0 ) += ( c->volume_left * ( (short)c->tail.fade.initial >> 4 ) ) >> 3;
        *( dest + 4 ) += ( c->volume_right * ( (short)c->tail.fade.initial >> 4 ) ) >> 3;
        dest++;
        c->tail.fade.initial += c->tail.fade.remaining;
        *( dest + 0 ) += ( c->volume_left * ( (short)c->tail.fade.initial >> 4 ) ) >> 3;
        *( dest + 4 ) += ( c->volume_right * ( (short)c->tail.fade.initial >> 4 ) ) >> 3;
        dest++;
        c->tail.fade.initial += c->tail.fade.remaining;
        *( dest + 0 ) += ( c->volume_left * ( (short)c->tail.fade.initial >> 4 ) ) >> 3;
        *( dest + 4 ) += ( c->volume_right * ( (short)c->tail.fade.initial >> 4 ) ) >> 3;
        dest++;
        c->tail.fade.initial += c->tail.fade.remaining;

        c->volume_table_index -= 4;
        amount -= 4;
        dest += 4;
    }

    if( !c->volume_table_index ) {
        c->active = 0;
    }

    if( amount ) {
        audio_mix_sample_bias( dest, amount, c->volume_left, c->volume_right );
    }
}
