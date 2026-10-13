#include "audio_frame.h"

#define AUDIO_REG16(address) (*(volatile unsigned short *)(address))
#define AUDIO_REG32(address) (*(volatile unsigned int *)(address))

/* Register ordering and the zero-mode branch follow the original hardware path. */
void audio_initialize_hardware(int enabled)
{
    g_audio_hardware_enabled = enabled;
    AUDIO_REG16(0x04000084) = 0x80;
    AUDIO_REG16(0x04000082) = 0x9A0C;
    if (!(unsigned char)enabled) {
        AUDIO_REG16(0x04000082) |= 0x100;
        AUDIO_REG16(0x04000082) &= 0x0FFF;
    }
    AUDIO_REG32(0x40000bc) = (unsigned int)g_audio_left_buffer;
    AUDIO_REG32(0x40000c8) = (unsigned int)g_audio_right_buffer;
    AUDIO_REG32(0x40000c0) = 0x040000A0;
    AUDIO_REG32(0x40000cc) = 0x040000A4;
    AUDIO_REG16(0x40000c6) = 0xB640;
    if ((unsigned char)enabled) AUDIO_REG16(0x40000d2) = AUDIO_REG16(0x40000c6);
    AUDIO_REG16(0x04000104) = 0xFBCD;
    AUDIO_REG16(0x04000106) = 0xC4;
    AUDIO_REG16(0x04000100) = 0xFC00;
    g_audio_buffer_phase = 2;
    g_audio_buffer_offset = 552;
    g_audio_previous_stamp = 0;
    g_audio_stamp = 0;
}
