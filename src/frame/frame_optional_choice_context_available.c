#include "frame_optional_choice_context.h"

unsigned int frame_optional_choice_context_available(struct FrameNeedEffectState *owner,
                                                      struct FrameObject *object)
{
    struct FrameOptionalChoiceContextState *state =
        (struct FrameOptionalChoiceContextState *)owner;
    if (state->active == 1)
        return 0;
    if (frame_count_actor_attachments(object) && state->attachment_mode == 1)
        return 0;
    if (!frame_object_has_zero_id(object))
        return 0;
    return 1;
}
