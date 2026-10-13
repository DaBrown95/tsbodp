#include "frame_need_effect_optional.h"

unsigned int frame_need_effect_try_optional(struct FrameNeedEffectState *state)
{
    if (state->enabled && state->optional != 1) {
        if (frame_random_secondary_chance(
                g_frame_need_optional_thresholds[state->kind].threshold) == 1) {
            unsigned short amount = 25600;
            state->optional = 1;
            state->parameter = amount;
            frame_need_effect_play_optional_cue(state);
            if (((struct FrameNeedOptionalObjectView *)state->object)->object_slot_90) {
                transition_object_set_state(
                    ((struct FrameNeedOptionalObjectView *)state->object)->object_slot_90, 1);
                ((struct FrameNeedOptionalObjectView *)state->object)->object_slot_90 = 0;
            }
            return 1;
        }
    }
    return 0;
}
