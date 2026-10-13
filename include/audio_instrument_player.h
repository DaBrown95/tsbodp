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
#ifndef AUDIO_INSTRUMENT_PLAYER_H
#define AUDIO_INSTRUMENT_PLAYER_H
#include "audio_player_decode.h"
#include "audio_pitch.h"
typedef union { struct { unsigned int channel:8,id:24; }; unsigned int val; } AudioInstrumentHandle;
extern struct AudioPlayerTrack g_audio_instrument_tracks[];
extern unsigned int g_audio_instrument_generation;
unsigned int audio_sample_active_ram(unsigned int) __attribute__((long_call));
unsigned int audio_sample_active(unsigned int);
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed char s8;typedef int bool;
#define true 1
#define false 0
static inline void stopChannel( struct AudioPlayerTrack *c )
{
    c->envelope_enabled = false;
    audio_sample_release( c->handle );
}
static inline bool i_init( struct AudioPlayerTrack *c )
{

    bool ret = false;
    c->envelope_enabled = false;
    c->i_vibrpos = 0;

    // volume-envelope?
    if( c->instrument->envVol.flags & ENVFLAGS_ENABLED ) {
        c->i_vol_status = ENVSTATUS_ACTIVE;
        c->i_vol_node = c->i_vol_tick = -1;
        c->i_vol_ticktarget = 0;

        c->i_vol_fade = 32767;
        c->i_vol_fadeactive = false;

        c->envelope_enabled = true;
        ret = true;
    }
    else {
        c->i_vol = 64;
        c->i_vol_status = ENVSTATUS_DISABLED;
    }

    // pan-envelope?
    if( c->instrument->envPan.flags & ENVFLAGS_ENABLED ) {
        c->i_pan_status = ENVSTATUS_ACTIVE;
        c->i_pan_node = c->i_pan_tick = -1;
        c->i_pan_ticktarget = 0;
        c->envelope_enabled = true;
    }
    else {
        c->i_pan = 0;
        c->i_pan_status = ENVSTATUS_DISABLED;
    }

    return ret;
}
static inline void i_release( struct AudioPlayerTrack *c )
{
    if( c->i_vol_status ) {
        c->i_vol_fadeactive = true;
        if( c->i_vol_status == ENVSTATUS_SUSTAIN )
            c->i_vol_status = ENVSTATUS_ACTIVE;
        else
            c->i_vol_status = ENVSTATUS_ACTIVE_NOSUSTAIN;

        // this is ok here, cause w/o a volume-envelope === will stop the sample
        {
            if( c->i_pan_status == ENVSTATUS_SUSTAIN )
                c->i_pan_status = ENVSTATUS_ACTIVE;
            else
                c->i_pan_status = ENVSTATUS_ACTIVE_NOSUSTAIN;
        }
    }
    else {
        stopChannel( c );
    }
}
static inline u16 calcPeriodLinear(u32 n,const struct AudioSample *s) {return (n<<6)+2*768+(s->fine_tune>>1);}
static inline u32 calcFinalFreqLinear(u32 p) {int octave,rem;octave=((p>>6)*0xaaab)>>19;rem=p-octave*768;return g_audio_linear_frequencies[rem]>>(23-octave);}
void audio_set_master_volume(unsigned int);
void audio_instrument_initialize(void);
AudioInstrumentHandle audio_instrument_start(const struct AudioInstrument *,int,AudioInstrumentHandle);
int audio_instrument_release(AudioInstrumentHandle);
int audio_instrument_stop(AudioInstrumentHandle);
int audio_instrument_handle_valid(AudioInstrumentHandle);
void audio_instrument_process(void);
void audio_initialize(int);
void audio_player_stop_jingle(void);
void audio_player_set_channel_volume(unsigned int,unsigned int);
unsigned int audio_player_get_channel_volume(unsigned int);
#endif
