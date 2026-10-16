#include "frame_actor_attachment_palette_jobs.h"

unsigned int frame_step_attachment_palette_job_9(struct FrameNeedEffectState *owner,
                   struct FrameActorAttachmentRecord *job)
{
    unsigned int result = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_set_actor_direction(job->actor, g_actor_reverse_directions[
            ((struct FrameActorObject *)owner->object)->direction]);
        job->timer = 62;
        frame_request_animation((struct FrameCommandObject *)job->actor, 58);
        break;
    case 62:
        if (job->actor->flags & 0x400000) {
        audio_play_animation_cue(25);
            if (++((struct FrameAttachmentPaletteState *)&g_frame_interaction_settings)->selectors[0] > 15)
                ((struct FrameAttachmentPaletteState *)&g_frame_interaction_settings)->selectors[0] = 0;
            frame_load_actor_group_palette(&g_frame_interaction_settings.attachment_mode, 0);
            job->timer = 1;
        }
        break;
    case 1:
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        result = 2;
        break;
    }
    return result;
}
asm(".align 2, 0");
