#include "frame_need_effect_placement.h"

void frame_need_effect_decrement_counter(struct FrameNeedEffectState *state,
 struct FrameNeedEffectState *unused)
{
 ((struct DisplayNeedEffectStateView *)state)->value_dc--;
}
