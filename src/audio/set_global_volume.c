#include "audio_sample.h"

void audio_set_global_volume(unsigned int volume)
{
    if (volume > 255) volume = 255;
    g_audio_global_volume = volume;
}
