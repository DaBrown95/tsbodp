/*
 * Adapted from Krawall's kramPlay in lib/mixer.arm.c.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: game sample/channel layout, observed mixer indices and mono pan,
 * and fixed-step playback parameters; verified at the RAM execution address.
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
#include "audio_playback.h"

unsigned int audio_start_sample(const struct AudioSample *sample, int table, unsigned int handle)
{
    return audio_start_sample_extended(sample, table, handle, sample->step, sample->volume, sample->pan);
}
