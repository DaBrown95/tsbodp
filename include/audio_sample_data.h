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
#ifndef AUDIO_SAMPLE_DATA_H
#define AUDIO_SAMPLE_DATA_H
/* Partial header observed by the row decoder and copied ARM playback routines. */
struct AudioSample {
    unsigned int loop_length;
    const unsigned char *end;
    unsigned int step;
    signed char fine_tune, relative_note;
    unsigned char volume;
    signed char pan;
    unsigned char loop_mode, mixing_flags, data[1];
};
#endif
