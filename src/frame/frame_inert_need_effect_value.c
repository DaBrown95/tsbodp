#include "frame_inert_need_effect.h"

unsigned char frame_inert_need_effect_value(struct FrameNeedEffectState *owner)
{
    return 100 + 12 * g_frame_need_effect_definitions[owner->kind].unknown_04[31];
}
