#include "display_actor_interaction.h"
#include "display_need_effect_lifecycle.h"
#include "frame_actor_target_jobs.h"

void frame_adjust_attachment_need(struct FrameActorNeedState *needs, unsigned int amount)
{
    if (frame_world_in_idle_exclusion_set(g_frame_world_id))
        frame_adjust_actor_needs(needs, 0, (unsigned char)amount);
    else
        frame_adjust_actor_needs(needs, 56, (unsigned char)amount);
}
asm(".align 2, 0");
