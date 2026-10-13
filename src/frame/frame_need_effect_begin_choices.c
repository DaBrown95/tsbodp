#include "frame_grid_selection.h"
unsigned char frame_need_effect_begin_choices(struct FrameObject *base,struct FrameObject *actor)
{
 struct FrameNeedEffectChoiceObject *object=(struct FrameNeedEffectChoiceObject *)base;
 struct FrameNeedEffectState *owner=object->owner;
 if(((struct FrameActionOwnerCallbacks *)owner)->check(owner,actor)==1 && frame_need_effect_build_choices(base)==1) {
  object->actor=actor;
  object->phase=1;
  transition_object_set_state(actor,0);
  frame_set_variant_state(actor,7);
  return 1;
 }
 return 0;
}
asm(".align 2,0");
