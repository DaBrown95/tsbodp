#include "frame_actor_attachment_jobs_16_17.h"

unsigned int frame_step_attachment_job_17_2bd38(struct FrameNeedEffectState *owner,
                                               struct FrameActorAttachmentRecord *job)
{
    struct FrameAttachmentSelectionWorld *world;
    transition_object_set_state(owner->object,1);
    world = (struct FrameAttachmentSelectionWorld *)&g_resource_game_state;
    world->selected = 255;
    if((world->pending.word & 0x00ff00ff) == 0x00010032) {
        if((signed char)condition_query_actor(world->entries,
                world->pending.bytes.kind + 195) != -1) {
            world->pending.bytes.active = 0;
            world->pending.bytes.timer = 50;
        }
    }
    return 2;
}
asm(".align 2,0");
