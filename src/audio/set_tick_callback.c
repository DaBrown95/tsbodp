#include "audio_frame.h"
void audio_set_tick_callback(void (*callback)(void))
{
    g_audio_tick_callback = callback;
    if (callback) g_audio_tick_samples = g_audio_saved_tick_samples;
    else g_audio_saved_tick_samples = g_audio_tick_samples;
}
