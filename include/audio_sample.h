#ifndef AUDIO_SAMPLE_H
#define AUDIO_SAMPLE_H
/* Partial 44-byte backend channel view; names describe observed operations. */
struct AudioSampleChannel {
 unsigned char volume;
 signed char pan;
 unsigned char active, unknown03;
 const unsigned char *start, *cursor;
 unsigned int unknown0c[2];
 int step;
 unsigned int handle;
 unsigned short unknown1c;
 unsigned char volume_left, volume_right, mixing_mode, unknown21;
 unsigned char mixing_flags, unknown23;
 /* +24 selects the volume table while playing; stop/fade code reuses it. */
 unsigned char volume_table_index, unknown25[3];
 unsigned short fade_initial, fade_remaining;
};
extern struct AudioSampleChannel g_audio_sample_channels[32];
extern unsigned char g_audio_sample_fade_enabled, g_audio_sample_mix_mode;
extern unsigned char g_audio_sample_volume_table[];
extern unsigned char g_audio_global_volume;
unsigned int audio_sample_active(unsigned int);
unsigned int audio_sample_release(unsigned int);
int audio_set_sample_step(unsigned int,int);
void audio_set_global_volume(unsigned int);
void audio_mark_channels(int,int);
void audio_resume_channels(int);
void audio_clear_channels(int);
void audio_update_channel_volumes(void);
void audio_configure_mix_mode(int);
#endif
