#include "frame_actor_spawn_attachment.h"

unsigned int frame_step_actor_spawn_attachment(struct FrameNeedEffectState *owner,
                                              struct FrameActorAttachmentRecord *job)
{
    struct FramePoint point;
    if (job->timer == 0) {
        frame_commit_need_effect(owner->object, 3);
        frame_attachment_position(owner->object, 0, &point);
        frame_create_actor(4, ((struct FrameActorObject *)owner->object)->direction,
                           point.x, point.y);
        audio_play_animation_cue(49);
        owner->parameter = 1;
        job->timer = 1;
    }
    return 2;
}
