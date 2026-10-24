#include "frame_actor_attachment_no_choice.h"

unsigned int frame_prepare_no_choice_attachment(struct FrameNeedEffectState *owner,
                                                struct FrameObject *actor,
                                                unsigned int kind)
{
    switch (kind) {
    case 68:
    case 70:
    case 72:
        return 1;
    default:
        return 1;
    }
}
