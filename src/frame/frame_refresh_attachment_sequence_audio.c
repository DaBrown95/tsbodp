#include "frame_actor_attachment_sequence_jobs.h"
void frame_refresh_attachment_sequence_audio(struct FrameNeedEffectState *owner)
{
    if ((short)owner->parameter == 0xa00)
        audio_select_sequence(5);
    else
        audio_select_sequence(6);
    g_audio_control.flags |= 8;
}
