#include "frame_route_attachment_21_45.h"

unsigned int frame_prepare_route_attachment_12b4c(struct FrameNeedEffectState *owner,
                                                    struct FrameObject *actor,
                                                    unsigned int kind)
{
    switch (kind) {
    case 21:
    case 45:
        return 1;
    default:
        return 1;
    }
}
