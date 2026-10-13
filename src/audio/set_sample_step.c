#include "audio_sample.h"
int audio_set_sample_step(unsigned int handle, int step)
{
 struct AudioSampleChannel *channel = &g_audio_sample_channels[handle & 255];
 if (channel->handle != handle) return 0;
 if (channel->step >= 0) channel->step = step << 2;
 else channel->step = -(step << 2);
 return 1;
}
