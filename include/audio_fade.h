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
#ifndef AUDIO_FADE_H
#define AUDIO_FADE_H
#include "audio_sample.h"
void audio_mix_sample_bias(short *,unsigned int,unsigned int,unsigned int) __attribute__((long_call));
void audio_mix_sample_fade(struct AudioSampleChannel *,short *,unsigned int);
#endif
