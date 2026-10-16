#include "frame_need_effect_placement.h"
#include "frame_actor_finish.h"

void frame_need_effect_handoff_bounds(struct FrameObject *base,
 struct FrameNeedEffectState *state, unsigned char before)
{
 struct FrameObject *object = base;
 object->before_step = 0;
 if (before) {
  object->spatial.bounds.lower.x = object->spatial.bounds.upper.x =
   ((struct DisplayNeedEffectStateView *)state)->object->spatial.bounds.upper.x - 1;
  object->spatial.bounds.lower.y = object->spatial.bounds.upper.y =
   ((struct DisplayNeedEffectStateView *)state)->object->spatial.bounds.upper.y + 1;
 } else {
  object->spatial.bounds.lower.x = object->spatial.bounds.upper.x =
   ((struct DisplayNeedEffectStateView *)state)->object->spatial.bounds.upper.x + 1;
  object->spatial.bounds.lower.y = object->spatial.bounds.upper.y =
   ((struct DisplayNeedEffectStateView *)state)->object->spatial.bounds.upper.y - 1;
 }
}
