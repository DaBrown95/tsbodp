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
#ifndef AUDIO_VOLUME_EFFECTS_H
#define AUDIO_VOLUME_EFFECTS_H
#include "audio_pitch_effects.h"
#define EFF_VIBRATO 20
#define EFF_VOLSLIDE_VIBRATO_XM 49
static inline int setChannelVol(struct AudioPlayerTrack *c) { return audio_set_channel_volume(c->handle,c->volume*c->cvolume*c->i_vol >>12); }
static inline int setChannelPan(struct AudioPlayerTrack *c) { s8 x=c->panning+c->i_pan;F_CLIP(x,-64);C_CLIP(x,64);return audio_set_channel_pan(c->handle,x); }
static inline void setGlobalVol(void) { audio_set_global_volume(g_audio_player_volume_current*(g_audio_player.song?AUDIO_CURRENT_MODULE->global_volume*g_audio_player.volume:128*64)>>13);audio_update_channel_volumes(); }
inline static void volUp( struct AudioPlayerTrack *c, u32 v )
{
    c->volume += v;
    C_CLIP( c->volume, 64 );
    setChannelVol( c );
}
inline static void volDown( struct AudioPlayerTrack *c, u32 v )
{
    c->volume -= v;
    F_CLIP( c->volume, 0 );
    setChannelVol( c );
}
inline static void volSet( struct AudioPlayerTrack *c, u32 v )
{
    c->volume = v;
    C_CLIP( c->volume, 64 );
    setChannelVol( c );
}
inline static void panRight( struct AudioPlayerTrack *c, u32 p )
{
    c->panning += p;
    C_CLIP( c->panning, 64 );
    setChannelPan( c );
}
inline static void panLeft( struct AudioPlayerTrack *c, u32 p )
{
    c->panning -= p;
    F_CLIP( c->panning, -64 );
    setChannelPan( c );
}
inline static void panSet( struct AudioPlayerTrack *c, int p )
{
    c->panning = p;
    C_CLIP( c->panning, 64 );
    F_CLIP( c->panning, -64 );
    setChannelPan( c );
}
#define TABLE_PERIODS_LENGTH 120
static inline int quickModulo(int a,int b) {int ret;audio_bios_remainder_thumb(a,b,&ret);return ret;}
static inline void setChannelPosH(struct AudioPlayerTrack *c,u32 pos) {audio_set_channel_position(c->handle,pos<<8);}
static inline u16 calcPeriodLinear(u32 n,const struct AudioSample *s) {return (n<<6)+2*768+(s->fine_tune>>1);}
static inline u32 calcFinalFreqLinear(u32 p) {int octave,rem;octave=((p>>6)*0xaaab)>>19;rem=p-octave*768;return g_audio_linear_frequencies[rem]>>(23-octave);}
static inline void setChannelFreqNote(struct AudioPlayerTrack *c,u32 n) {c->periodc=calcPeriodLinear(n,c->sample);audio_set_sample_step(c->handle,calcFinalFreqLinear(c->periodc));}
#endif
