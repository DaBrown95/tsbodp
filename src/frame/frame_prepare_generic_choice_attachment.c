#include "frame_actor_attachment_generic_choice.h"

unsigned int frame_prepare_generic_choice_attachment(struct FrameNeedEffectState *owner,
                                                      struct FrameObject *actor,
                                                      unsigned int kind)
{
    switch (kind) {
    case 40:
        return 1;
    default:
        return 1;
    }
}
