#include "frame_group_selector.h"

void frame_group_selector_step(struct FrameObject *base)
{
 struct FrameGroupSelectorObject *object=(struct FrameGroupSelectorObject *)base;
 switch(object->state) {
 case 0: break;
 case 1: frame_run_actor_state(base); break;
 }
}
asm(".align 2, 0");
