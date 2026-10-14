#include "frame_placement_session.h"
void frame_placement_reset_parameter(struct FrameObject *base)
{
 struct FrameNeedEffectObject *object=(struct FrameNeedEffectObject *)base;
 struct FrameNeedEffectState *state=object->effect_state;
 unsigned int kind=state->kind;
 if(kind-44<=1 || kind==49) { if(state->optional!=1)state->parameter=0; }
 if(kind-106<=2) { state=object->effect_state; if(state->optional!=1)state->parameter=512; }
 if(kind==104 || kind==42 || kind==43) { state=object->effect_state; if(state->optional!=1)state->parameter=0; }
}

asm(".align 2,0");
