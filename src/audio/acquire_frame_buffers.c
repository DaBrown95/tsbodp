#include "audio_frame.h"

int __attribute__((long_call)) audio_acquire_frame_buffers(unsigned char **left, unsigned char **right)
{
    unsigned int offset;
    int amount;
    unsigned int *offset_address;
    unsigned int *phase_address;
    if (g_audio_ring_enabled) {
        offset = g_audio_buffer_offset;
        *left = g_audio_left_buffer + offset;
        *right = g_audio_right_buffer + offset;
        if (g_audio_stamp == g_audio_previous_stamp) goto advance;
        g_audio_previous_stamp = g_audio_stamp;
        if (g_audio_buffer_phase - 1 <= 1) goto advance;
    }
    return 0;
advance:
    offset_address = &g_audio_buffer_offset;
    amount = 276;
    *offset_address += amount;
    phase_address = &g_audio_buffer_phase;
    if (++*phase_address > 3) {
        *phase_address = 0;
        *offset_address = 0;
    }
    return amount;
}
