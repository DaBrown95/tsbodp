#include "frame_actor_attachment_jobs_3_4_18.h"

unsigned int frame_initialize_attachment_jobs_3_4_18(struct FrameNeedEffectState *owner)
{
    struct FrameAttachmentSequenceMode *work = (struct FrameAttachmentSequenceMode *)owner;
    work->enabled = 1;
    if (g_scene_id == 20 && g_scene_context.period == 1)
        work->enabled = 0;
    return 1;
}
