#include "frame_optional_playback.h"

unsigned int frame_prepare_optional_playback_attachment_kind(struct FrameNeedEffectState *owner,
                                                struct FrameObject *actor,
                                                unsigned int kind)
{
    switch (kind) {
    case 1:
    case 6:
    case 45:
    case 56:
    case 57:
    case 62:
        return 1;
    default:
        return 1;
    }
}
