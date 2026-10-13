#include "frame_need_effect_optional_state.h"

void frame_need_effect_set_optional_one(struct FrameNeedEffectState *state,unsigned short parameter)
{
 state->optional=1;
 state->parameter=parameter;
 frame_need_effect_play_optional_cue(state);
 if(((struct FrameNeedOptionalObjectView *)state->object)->object_slot_90) {
  transition_object_set_state(((struct FrameNeedOptionalObjectView *)state->object)->object_slot_90,1);
  ((struct FrameNeedOptionalObjectView *)state->object)->object_slot_90=0;
 }
}
asm(".align 2, 0");
