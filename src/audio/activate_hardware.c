#include "audio_frame.h"
void audio_activate_hardware(void) {
 *(volatile unsigned short *)0x04000200 |= 16;
 *(volatile unsigned short *)0x04000102 = 128;
 g_audio_ring_enabled = 1;
}
