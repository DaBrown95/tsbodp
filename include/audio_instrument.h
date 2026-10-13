/*
 * Layout names adapted from Krawall lib/player.c and lib/mtypes.h.
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl.
 * Source: https://github.com/sebknzl/krawall/tree/8d338581bf0ed0afad15b66bf5979ad4c4d15ed0
 * Changes: observed partial game layouts and direct mixer handoff declarations.
 * LGPL-2.1-or-later; see licenses/Krawall-LGPL-2.1.txt for the licence.
 */
#ifndef AUDIO_INSTRUMENT_H
#define AUDIO_INSTRUMENT_H
#include "audio_player.h"

/* Naturally aligned partial views; the first instrument region is unclassified. */
struct AudioEnvelopeNode { unsigned short coord, inc; };
struct AudioEnvelope {
    struct AudioEnvelopeNode nodes[12];
    unsigned char max, sus, loopStart, flags;
};
struct AudioInstrument {
    unsigned char unknown00[192];
    struct AudioEnvelope envVol, envPan;
    unsigned short volFade;
    unsigned char vibType, vibSweep, vibDepth, vibRate;
};
/* These accepted routines execute in ARM RAM; the caller needs a long transfer. */
int audio_set_channel_volume(unsigned int, unsigned int) __attribute__((long_call));
int audio_set_channel_pan(unsigned int, int) __attribute__((long_call));
int audio_set_sample_step(unsigned int, int) __attribute__((long_call));
unsigned int audio_sample_release(unsigned int) __attribute__((long_call));

#define AUDIO_ENV_SUSTAIN 2
#define AUDIO_ENV_LOOP 4
#define AUDIO_ENV_STOPPED 1
#define AUDIO_ENV_SUSTAINING 2
#define AUDIO_ENV_ACTIVE 3
#define AUDIO_ENV_ACTIVE_NOSUSTAIN 4
#endif
