#include "frame_trigger_objects.h"

void frame_program_trigger_interact(struct FrameObject *base,struct FrameObject *other)
{
 struct FrameTriggerObject *object=(struct FrameTriggerObject *)base;
 if(other->id!=0) return;
 if(object->kind==0) transition_object_set_state((struct TransitionObject *)base,5);
 else transition_object_set_state((struct TransitionObject *)base,4);
 object->flags&=~4;
}
asm(".align 2, 0");
