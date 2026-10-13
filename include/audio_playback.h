#ifndef AUDIO_PLAYBACK_H
#define AUDIO_PLAYBACK_H
#include "audio_sample.h"
#include "audio_frame.h"

#include "audio_sample_data.h"

extern unsigned int g_audio_channel_counter;

unsigned int audio_start_sample(const struct AudioSample *, int, unsigned int);
unsigned int audio_start_sample_extended(const struct AudioSample *, int,
    unsigned int, unsigned int, unsigned int, int);
int audio_set_channel_volume(unsigned int, unsigned int);
int audio_set_channel_pan(unsigned int, int);
int audio_set_channel_position(unsigned int, unsigned int);
#endif
