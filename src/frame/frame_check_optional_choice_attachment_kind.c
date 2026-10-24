#include "frame_optional_choice_context.h"
unsigned int frame_check_optional_choice_attachment_kind(struct FrameNeedEffectState *owner, struct FrameObject *object, unsigned int kind)
{
    if (!frame_object_has_zero_id(object))
        return 0;
    switch (kind) {
    case 41:
    case 45:
        return 1;
    default:
        return 1;
    }
}
