#include "display_actor_interaction.h"
#include "frame_actor_counter_attachment_job_12.h"

unsigned int frame_check_counter_attachment_job_12(struct FrameNeedEffectState *owner,
                                          struct FrameObject *actor)
{
    if (frame_count_actor_attachments(actor) && owner->unknown_60[0] == 1)
        return 0;
    return 1;
}
asm(".align 2, 0");
