/*
 * Adapted from Krawall lib/player.c and lib/mtypes.h.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: observed game layouts, direct RAM mixer transfers and the earlier
 * order-jump, callback and channel-stop behavior. Ordinary C at original entries.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the GNU Lesser General Public License as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at your option) any later
 * version.
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See licenses/Krawall-LGPL-2.1.txt for the licence.
 */
#ifndef AUDIO_PLAYER_DECODE_H
#define AUDIO_PLAYER_DECODE_H
#include "audio_sequence_player.h"
#include "audio_instrument.h"
#include "audio_sample_data.h"
extern const struct AudioSample *g_audio_player_samples[];
extern const struct AudioInstrument *g_audio_player_instruments[];
unsigned int audio_start_sample_extended(const struct AudioSample *, int, unsigned int, unsigned int, unsigned int, int) __attribute__((long_call));
int audio_set_channel_position(unsigned int, unsigned int) __attribute__((long_call));
#define F_CLIP(x,y) { if(x<y)x=y; }
#define C_CLIP(x,y) { if(x>y)x=y; }
#define EFF_PORTA_NOTE 19
#define EFF_VOLSLIDE_PORTA 24
#define ENVFLAGS_ENABLED 1
#define ENVSTATUS_DISABLED 0
#define ENVSTATUS_ACTIVE 3
#define ENVSTATUS_SUSTAIN 2
#define ENVSTATUS_ACTIVE_NOSUSTAIN 4
#endif
