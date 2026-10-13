#include "display_need_effect_progress.h"
unsigned char frame_need_effect_action_available(struct FrameNeedEffectState *state,unsigned int incoming)
{
 unsigned int action=incoming;
 register unsigned int group asm("r3")=0;
 unsigned int i,flags;
 unsigned char *data,*loaded;
 /* The work flags are read as a word; only the low half controls availability. */
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
asm(".align 2, 0");
