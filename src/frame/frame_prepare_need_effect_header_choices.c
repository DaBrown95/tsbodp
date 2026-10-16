#include "frame_need_effect_header_choices.h"

unsigned int frame_prepare_need_effect_header_choices(struct FrameNeedEffectState *owner,
                                                struct FrameObject *actor,
                                                unsigned int kind)
{
    switch (kind) {
    case 49:
    case 50:
        return 1;
    default:
        return 1;
    }
}
