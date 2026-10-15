#include "frame_need_effect_header_choices.h"
#include "frame_need_effect_optional_jobs.h"
unsigned int frame_need_effect_check_actor_header_variant(struct FrameNeedEffectState *owner,struct FrameObject *actor)
{
    if (frame_count_actor_attachments(actor) && owner->unknown_60[0] == 1)
        return 0;
    if (actor->id == 7 && actor->unknown_0a <= 31)
        return 0;
    return 1;
}
