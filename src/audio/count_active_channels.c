#include "audio_sample.h"
unsigned int audio_count_active_channels(void) {
 unsigned int count=0, remaining=32;
 struct AudioSampleChannel *channel=g_audio_sample_channels;
 do { if(channel->active==1) count++; channel++; remaining--; } while(remaining);
 return count;
}
