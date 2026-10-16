#include "frame_actor_attachment_control_jobs.h"

void frame_refresh_attachment_control_174a8(struct FrameNeedEffectState *owner)
{
    if ((short)owner->parameter == 0xa00)
        audio_select_sequence(21);
    if ((short)owner->parameter == 0xb00)
        audio_select_sequence(7);
    if ((short)owner->parameter == 0xc00)
        audio_select_sequence(22);
    g_audio_control.flags |= 8;
}
