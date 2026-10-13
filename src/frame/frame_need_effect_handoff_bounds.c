#include "frame_need_effect_placement.h"
#include "frame_actor_finish.h"

void frame_need_effect_handoff_bounds(struct FrameObject *base,
 struct FrameNeedEffectState *state, unsigned char before)
{
 struct FrameActorFinishBounds *object = (struct FrameActorFinishBounds *)base;
 object->before_step = 0;
 if (before) {
  object->lower.x = object->upper.x =
   ((struct FrameActorFinishBounds *)((struct DisplayNeedEffectStateView *)state)->object)->upper.x - 1;
  object->lower.y = object->upper.y =
   ((struct FrameActorFinishBounds *)((struct DisplayNeedEffectStateView *)state)->object)->upper.y + 1;
 } else {
  object->lower.x = object->upper.x =
   ((struct FrameActorFinishBounds *)((struct DisplayNeedEffectStateView *)state)->object)->upper.x + 1;
  object->lower.y = object->upper.y =
   ((struct FrameActorFinishBounds *)((struct DisplayNeedEffectStateView *)state)->object)->upper.y - 1;
 }
}
