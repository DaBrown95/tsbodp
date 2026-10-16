#ifndef AUDIO_QUERIES_H
#define AUDIO_QUERIES_H
#include "audio_sample.h"
/* These backend queries use only the handle's low byte, without validation. */
unsigned int audio_get_channel_frequency(unsigned int);
unsigned int audio_get_channel_volume(unsigned int);
int audio_get_channel_pan(unsigned int);
unsigned int audio_get_channel_position(unsigned int);
unsigned int audio_mixer_get_sample_volume(void);
extern int g_audio_player_volume_target;
unsigned int audio_player_get_volume_target(void);
#endif
