#include "save_stream.h"
#include "audio_frame.h"

void save_stream_suspend_audio(void)
{
    audio_deactivate_hardware();
}
asm(".align 2, 0");
