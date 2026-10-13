#include "audio_sample.h"
unsigned int audio_sample_active(unsigned int handle)
{
 return g_audio_sample_channels[(unsigned char)handle].handle==handle &&
        g_audio_sample_channels[(unsigned char)handle].active ? 1 : 0;
}
