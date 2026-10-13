#include "frame_need_effect_optional_state.h"

void frame_need_effect_begin_optional_three(struct FrameNeedEffectState *state)
{
 struct FrameObject *other;
 state->optional=3;
 state->parameter=12800;
 if(frame_find_objects(5,41,&other,1)) {
  struct FrameNeedEffectState *work=((struct FrameNeedEffectObject *)other)->effect_state;
  ((struct FrameNeedOptionalApplyCallbacks *)work)->apply(work,0,0);
 }
 if(((struct FrameNeedOptionalObjectView *)state->object)->object_slot_90) {
  transition_object_set_state(((struct FrameNeedOptionalObjectView *)state->object)->object_slot_90,1);
  ((struct FrameNeedOptionalObjectView *)state->object)->object_slot_90=0;
 }
}
asm(".align 2, 0");
