#ifndef AUDIO_PLAYBACK_H
#define AUDIO_PLAYBACK_H
#include "audio_sample.h"
#include "audio_frame.h"

/* Partial sample header observed by the copied ARM playback routines. */
struct AudioSample {
    unsigned int loop_length;
    const unsigned char *end;
    unsigned int step;
    unsigned short unknown0c;
    unsigned char volume;
    signed char pan;
    unsigned char loop_mode, mixing_flags, data[1];
};

unsigned int audio_start_sample(const struct AudioSample *, int, unsigned int);
unsigned int audio_start_sample_extended(const struct AudioSample *, int,
    unsigned int, unsigned int, unsigned int, int);
int audio_set_channel_volume(unsigned int, unsigned int);
int audio_set_channel_pan(unsigned int, int);
int audio_set_channel_position(unsigned int, unsigned int);
#endif
