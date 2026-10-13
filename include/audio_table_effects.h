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
#ifndef AUDIO_TABLE_EFFECTS_H
#define AUDIO_TABLE_EFFECTS_H
#include "audio_volume_effects.h"
#define KRAM_SP_CENTER 0
static inline void audio_player_play_track(struct AudioPlayerTrack *c) {c->resetnote=0;c->handle=audio_start_sample_extended(c->sample,0,c->handle,g_audio_player.calc_final_frequency(c->period),c->volume*c->cvolume>>6,c->panning);if(c->pos)setChannelPosH(c,c->pos);}
static inline void setChannelPos(struct AudioPlayerTrack *c) {audio_set_channel_position(c->handle,(u32)c->pos<<8);}
void audio_effect_portamento_note(struct AudioPlayerTrack *,int);
#endif
