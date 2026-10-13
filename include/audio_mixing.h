#ifndef AUDIO_MIXING_H
#define AUDIO_MIXING_H
#include "audio_sample.h"
#include "audio_frame.h"
/* Stereo intermediate samples and dispatch edges observed in the copied mixer. */
extern short g_audio_mix_buffer[552];
extern int g_audio_volume_sum_left, g_audio_volume_sum_right;
typedef void (*AudioChannelMixFunction)(struct AudioSampleChannel *, short *, unsigned int);
extern AudioChannelMixFunction const g_audio_mix_functions[];
void audio_mix_clear(short *, unsigned int) __attribute__((long_call));
void audio_mix_downsample(short *, unsigned char *, unsigned char *, unsigned int) __attribute__((long_call));
void audio_mix_bias(short *, unsigned int, unsigned int, unsigned int) __attribute__((long_call));
#endif
