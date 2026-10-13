/*
 * Adapted from Krawall's mixReal in lib/mixer_private.arm.c.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: game channel layout and names, observed sample-step estimate, and
 * explicitly separate BIOS division glue; verified at the RAM execution address.
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
#include "audio_mixing.h"
#include "audio_bios_divide.h"

// a guess how many samples still fit
#define SAMPLEINCGUESS      ( ( (todo * (c->step >> 8)) >> 8 ) + 1 )
#define SAMPLEINCGUESSNEG   ( (todo * (c->step >> 8)) >> 8 )

#define LOOP_NORMAL     1
#define LOOP_BIDIR      2

// 'does' the loop
#define DOLOOP                              \
    if( c->loop_mode == LOOP_BIDIR ) {          \
        c->step = -c->step;                 \
    }                                       \
    else {                                  \
        c->cursor -= c->loop_length;            \
    }


// amount % 4 must be 0!
void audio_mix_channels( unsigned char *lbuffer, unsigned char *rbuffer, unsigned int amount )
{
    short *dest;

    // clear buffer
    audio_mix_clear( g_audio_mix_buffer, amount );

    int i;
    struct AudioSampleChannel* c = &g_audio_sample_channels[ 0 ];
    for( i = 32; i; i--, c++ ) {
        if( c->active != 1 )
            continue;

        int todo = amount;

        // 0-vol optimization
        if( !c->volume ) {
            unsigned int sampleinc = SAMPLEINCGUESS;
            if( c->loop_mode ) {
                if( c->loop_mode == LOOP_BIDIR ) {
                    if( c->step >= 0 ) {
                        c->cursor += sampleinc;
                        // if beyond end, move back into loop and change direction/position accordingly
                        int block;
                        for( block = 0; c->cursor >= c->end; c->cursor -= c->loop_length, block++ );
                        if( block & 1 ) { // odd
                            c->cursor = c->end - ( c->cursor - c->tail.loop_start );
                            c->step = -c->step;
                        }
                    }
                    else {  // same as above but when direction is negative
                        c->cursor += sampleinc;
                        int block;
                        for( block = 0; c->cursor < c->tail.loop_start; c->cursor += c->loop_length, block++ );
                        if( block & 1 ) { // odd
                            c->cursor = c->tail.loop_start + ( c->end - c->cursor );
                            c->step = -c->step;
                        }
                    }
                }
                else {
                    c->cursor += sampleinc;
                    // beyond end?
                    if( c->cursor >= c->end ) {
                        for( ; c->cursor >= c->end; c->cursor -= c->loop_length );
                    }
                }
            }
            else { // simple case, unlooped: either stop or continue
                if( c->cursor + sampleinc >= c->end ) {
                    c->active = 0;
                }
                else {
                    c->cursor += sampleinc;
                }
            }
            continue;
        }

        dest = g_audio_mix_buffer;

        g_audio_volume_sum_left += c->volume_left;
        g_audio_volume_sum_right += c->volume_right;
        // determine mix-func to be used
        AudioChannelMixFunction mixFunc = g_audio_mix_functions[ c->mix_function + c->mixing_mode ];

        int fitenough;
        int fit, rem;

      keepmixing:
        if( c->step >= 0 ) {
            // can we just mix? is the sample long enough?
            if( !( fitenough = ( c->cursor + SAMPLEINCGUESS < c->end ) ) ) {
                // no, calculate exactly how many samples will fit
                audio_bios_divide_remainder(
                    ( ( ( c->end - c->cursor ) << 14 ) - ( c->fraction >> 2 ) ), // '/'
                    ( c->step >> 2 ),
                    &fit, &rem );
            }
        }
        else {
            if( !( fitenough = ( c->cursor + SAMPLEINCGUESSNEG > c->tail.loop_start ) ) ) {

                audio_bios_divide_remainder(
                    ( ( ( c->cursor - c->tail.loop_start ) << 14 ) + ( c->fraction >> 2 ) ), // '/'
                    ( (-c->step) >> 2 ),
                    &fit, &rem );
            }
        }

        if( fitenough ) {
            // we can mix without hitting a loop-end, do that!
            mixFunc( c, dest, todo );
        }
        else {
            if( rem )
                fit++;

            // this can happen as well (guessing above isn't that accurate)
            if( fit > todo ) {
                mixFunc( c, dest, todo );
            }
            else { // fit <= todo
                // align fit to 4
                if( fit & 3 )
                    fit = ( ( fit >> 2 ) + 1 ) << 2;

                if( fit < todo ) {
                    if( fit ) {
                        mixFunc( c, dest, fit );

                        todo -= fit;
                        dest += 2*fit;
                    }

                    if( c->loop_mode ) {
                        DOLOOP;

                        if( todo ) {
                            goto keepmixing;
                        }
                    }
                    else {
                        c->active = 0;
                        audio_mix_bias( dest, todo, c->volume_left, c->volume_right );
                    }
                }
                else {  // fit == todo (not >todo since todo is aligned to 4 as well)
                    mixFunc( c, dest, fit );
                    if( c->loop_mode ) {
                        DOLOOP;
                    }
                    else
                        c->active = 0;
                }
            }
        }
    }

    // downsample
    audio_mix_downsample( g_audio_mix_buffer, lbuffer, rbuffer, amount );
}
