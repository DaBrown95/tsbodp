#include "audio_sample.h"
void audio_mixer_set_sample_volume(unsigned int volume) { if(volume>255)volume=255;g_audio_sample_volume_table[1]=volume; }
