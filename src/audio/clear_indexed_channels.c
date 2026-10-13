#include "audio_sample.h"
void audio_clear_indexed_channels(void) {
 struct AudioSampleChannel *channel=g_audio_sample_channels;
 unsigned int remaining=32;
 do { if(channel->volume_table_index && channel->active==1)channel->active=0; channel++; remaining--; } while(remaining);
}
