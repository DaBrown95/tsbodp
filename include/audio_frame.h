#ifndef AUDIO_FRAME_H
#define AUDIO_FRAME_H
/* Shared sequencer timing words and callback observed by the RAM frame mixer. */
extern unsigned char g_audio_left_buffer[1104], g_audio_right_buffer[1104];
extern unsigned int g_audio_buffer_offset, g_audio_buffer_phase;
extern unsigned int g_audio_previous_stamp, g_audio_ring_enabled;
extern volatile unsigned int g_audio_stamp;
extern unsigned char g_audio_hardware_enabled;
void audio_initialize_hardware(int);
void audio_activate_hardware(void);
void audio_deactivate_hardware(void);
int audio_acquire_frame_buffers(unsigned char **, unsigned char **) __attribute__((long_call));
int audio_mix_frame(void);
extern unsigned short g_audio_tick_samples, g_audio_tick_period;
extern unsigned short g_audio_saved_tick_samples;
extern void (*g_audio_tick_callback)(void);
void audio_set_tick_callback(void (*)(void));
extern void audio_mix_channels(unsigned char *, unsigned char *, unsigned int);
#endif
