#include "frame_need_effect_optional_state.h"
static inline int add_amount(int a,int b){return a+b;}
void frame_need_effect_accumulate_optional(struct FrameNeedEffectState *state)
{
 if(state->enabled&&state->optional!=1) {
  state->optional=2;
  {const struct FrameNeedOptionalThreshold *row;
  short *parameter;
  int amount,next;
  {const struct FrameNeedOptionalThreshold *table=g_frame_need_optional_thresholds;
  row=&table[state->kind];
  parameter=(short *)&state->parameter;
  next=*parameter;
  amount=row->increment;
  next+=amount;
  if(next<=0x63ff)state->parameter=add_amount(amount,state->parameter);
  else state->parameter=25600;
  }}
 }
}
asm(".align 2, 0");
