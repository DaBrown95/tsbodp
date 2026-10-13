#include "frame_need_effect_placement.h"

/* The local group index is constrained only within this call-free predicate. */
static inline unsigned char action_available(struct FrameNeedEffectState *state,unsigned int action)
{
 register unsigned int group asm("r3")=0;
 unsigned int i,flags;
 unsigned char *data,*loaded;
 if(action!=1) {
  if(action!=4)goto scan;
  flags=*(unsigned int *)((unsigned char *)state+0x74);
 } else flags=*(unsigned int *)((unsigned char *)state+0xa4);
 if(!(flags<<16))goto absent;
 goto found;
scan:
 loaded=g_need_effect_action_sets[state->kind];
 if(loaded)goto rows;
 goto absent;
found:return 1;
rows:
 data=loaded+2;
 do {
  unsigned char *entry;
  i=0;
  entry=(unsigned char *)(group*5+(unsigned int)data);
  for(;i<5;i++){if(*entry==action)goto found;entry++;}
  group++;
 }while(group<5);
absent:return 0;
}

struct FrameNeedEffectState *frame_need_effect_find_neighbor(const struct FrameActorPackedCell *cell,
 unsigned int action)
{
 struct FrameNeedEffectState *state=(struct FrameNeedEffectState *)g_frame_need_effect_active_list.first;
 while(state) {
  struct FrameNeedEffectState *next=((struct DisplayNeedEffectStateView *)state)->next;
  if(frame_need_effect_contains_cell(state,cell)==1) {
   if(action_available(state,action))return state;
  }
  state=next;
 }
 return 0;
}
asm(".align 2,0");
