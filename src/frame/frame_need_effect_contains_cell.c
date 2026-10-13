#include "frame_need_effect_placement.h"

unsigned char frame_need_effect_contains_cell(struct FrameNeedEffectState *state,
 const struct FrameActorPackedCell *cell)
{
 unsigned char i;
 for(i=0;i<=9;i++) {
  if(((struct FrameNeedEffectCells *)state)->cells[i].x==((const unsigned char *)cell)[0] &&
     ((struct FrameNeedEffectCells *)state)->cells[i].y==((const unsigned char *)cell)[1])return 1;
 }
 return 0;
}
asm(".align 2,0");
