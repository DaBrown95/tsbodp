#include "display_need_effect_update.h"

/* Incoming callers and any additional unused formals remain unknown. */
void frame_stop_pair_and_wait_unrooted_1133c(struct FrameObject *first,
                                           struct FrameObject *second)
{
    frame_need_effect_stop_at_position(first);
    frame_need_effect_stop_at_position(second);
    frame_set_variant_state(first, 7);
    ((struct DisplayNeedEffectActorView *)first)->timer = 60;
}

asm(".align 2, 0");
