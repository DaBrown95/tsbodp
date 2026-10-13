/*
 * Adapted from Krawall lib/player.c and lib/mtypes.h.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: packed game note/instrument encoding, direct sample defaults,
 * earlier envelope initialization and release, and copied ARM mixer handoffs.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the GNU Lesser General Public License as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at your option) any later
 * version.
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See licenses/Krawall-LGPL-2.1.txt for the licence.
 */
#include "audio_player_decode.h"
typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed char s8;typedef int bool;typedef u8 flag;
#define true 1
#define false 0
static inline void setChannelFreq( struct AudioPlayerTrack *c )
{
    c->periodc = c->period;
    audio_set_sample_step( c->handle, g_audio_player.calc_final_frequency( c->period ) );
}

static inline bool setChannelVol( struct AudioPlayerTrack *c )
{

    return audio_set_channel_volume( c->handle, c->volume * c->cvolume * c->i_vol >> 12 );
}
static inline bool setChannelPan( struct AudioPlayerTrack *c )
{

    s8 x = c->panning + c->i_pan;
    F_CLIP( x, -64 );
    C_CLIP( x, 64 );
    return audio_set_channel_pan( c->handle, x );
}
static inline void setChannelPos( struct AudioPlayerTrack *c )
{
    audio_set_channel_position( c->handle, ( u32 )c->pos << 8 );
}
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

static inline void playChannelNote( struct AudioPlayerTrack *c )
{

    c->resetnote = false;

    c->handle =
        audio_start_sample_extended(
            c->sample, 0, c->handle,
            g_audio_player.calc_final_frequency( c->period ),
            c->volume * c->cvolume >> 6, c->panning
        );

    if( c->pos )
        setChannelPos( c );
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

void audio_player_process_row(void)
{
    while( 1 ) {

        u8 follow = *g_audio_player.stream++;
        if( !follow )
            break;

        u8 note = 0, vol = 0, eff = 0, effop = 0;
        u16 instrument = 0;
        flag setVol = false;
        flag sampleSet = false;

        struct AudioPlayerTrack *c = &g_audio_player.tracks[ follow & 0x1f ];
        c->touched = true;

        // note/sample
        if( follow & 32 ) {
            note = *g_audio_player.stream++;
            instrument = *g_audio_player.stream++;
            instrument |= (note & 1) << 8;
            note >>= 1;
        }
        // volume
        if( follow & 64 ) {
            vol = *g_audio_player.stream++;
        }
        // effect
        if( follow & 128 ) {
            eff = *g_audio_player.stream++;
            effop = *g_audio_player.stream++;
        }

        c->leffect = c->effect;
        c->effect = eff;

        // was there an instrument? set vol & instrument/sample
        if( instrument ) {
            instrument--;
            if( g_audio_player.instrument_based ) {
                if( note ) {
                    c->instrument = g_audio_player_instruments[ instrument ];
                    c->sample = g_audio_player_samples[ c->instrument->samples[ note-1 ] ];
                    c->volume = c->sample->volume;

                    setVol = true;
                    sampleSet = true;
                }
            }
            else {
                c->sample = g_audio_player_samples[ instrument ];
                c->volume = c->sample->volume;
                setVol = true;
            }
        }

        // volume
        if( vol ) {
            if( vol <= 0x60 ) {
                c->volume = vol - 0x10;
                C_CLIP( c->volume, 0x40 );

                c->volume_effect = 0;
                setVol = true;
            }
            else {
                // volume-column-effects
                c->volume_effect = vol - 0x60;
                g_audio_volume_effects[ c->volume_effect >> 4 ].apply( c, true );
            }
        }
        c->playnote = false;

        // note && sample set
        if( note && c->sample ) {
            if( note-- == 0x7f ) { // The note-off comparison uses the value before decrement.
                i_release( c );
            }
            else {
                note += c->sample->relative_note;

                if( eff != EFF_PORTA_NOTE &&
                    eff != EFF_VOLSLIDE_PORTA ) {
                    if( g_audio_player.instrument_based ) {
                        if( !sampleSet )
                            c->sample = g_audio_player_samples[ c->instrument->samples[ note ] ];

                        c->panning = c->sample->pan;
                        i_init(c);
                    }

                    c->note = c->glissnote = note;
                    c->period = c->periodc = c->portadest = g_audio_player.calc_period( note, c->sample );
                    c->pos = 0;
                    c->trmcnt = 0;
                    c->playnote = true;
                }
                else {
                    c->portadest = g_audio_player.calc_period( note, c->sample );
                }
            }
        }

        c->effectop = effop;

        // call onrow-effect
        if( eff ) {
            if( g_audio_track_effects[ eff ].apply )
                g_audio_track_effects[ eff ].apply( c, true );
        }

        if( c->playnote ) {
            playChannelNote( c );
        }
        else if( setVol )
                setChannelVol( c );
    }

    // now let's go over all channels again
    // (some might have not been touched because there was no pattern-data)
    int i;
    struct AudioPlayerTrack *c = &g_audio_player.tracks[ 0 ];
    for( i = AUDIO_CURRENT_MODULE->channels; i; i-- ) {
        if( !c->touched ) {
            c->effectop = 0;
            c->leffect = c->effect;
            c->effect = 0;
            c->volume_effect = 0;
        }
        else {
            c->touched = false;
        }

        // must the note be reset? (freq/vol/pan)
        if( c->resetnote && ( c->effect != c->leffect ) ) {
            setChannelFreq( c );
            setChannelVol( c );
            setChannelPan( c );
            c->resetnote = false;
        }

        c++;
    }

    audio_player_advance_row();
}
