#include "frame_trigger_objects.h"

void frame_actor_trigger_interact(struct FrameObject *base,struct FrameObject *other)
{
 struct FrameTriggerObject *object=(struct FrameTriggerObject *)base;
 register struct FrameObject *target asm("r2")=other;
 if(target->id!=0) return;
 if(!(g_input_pressed[g_input_config.local_player]&1)) return;
 object->target=target;
 if(object->kind==0) transition_object_set_state((struct TransitionObject *)base,5);
 else transition_object_set_state((struct TransitionObject *)base,4);
 object->flags&=~4;
}
asm(".align 2, 0");
