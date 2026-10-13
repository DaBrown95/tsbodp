#include "save_stream.h"
#include "audio_frame.h"

void save_stream_resume_audio(void)
{
    audio_activate_hardware();
}
asm(".align 2, 0");
