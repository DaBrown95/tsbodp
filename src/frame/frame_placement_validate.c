#include "frame_placement_session.h"
unsigned char frame_placement_validate(void)
{
 unsigned char registered=frame_register_need_effect(g_frame_placement_session.grid,g_frame_placement_session.preview,1),reachable=0,result;
 if(registered==1) {
  struct FrameNeedEffectState *state=((struct FrameNeedEffectObject *)g_frame_placement_session.preview)->effect_state;
  unsigned char i=0;
  struct Candidate { unsigned int x:8,y:8,unknown:16; };
  struct Candidate cell=*(struct Candidate *)&((struct FrameNeedEffectCandidateCells *)state)->cells[0];
  while(cell.x || cell.y) {
   if(!frame_grid_search(g_frame_placement_session.grid,&g_frame_placement_session.original_cell,(struct FrameActorPackedCell *)&cell,50,0)) {
    i++;
    if(i>11)break;
    {unsigned int offset=i*sizeof(struct Candidate);
     const unsigned char *records=(const unsigned char *)state+0x74;
     cell=*(const struct Candidate *)(records+offset);}
   } else {reachable=1;break;}
  }
  frame_unregister_need_effect(g_frame_placement_session.grid,g_frame_placement_session.preview);
 }
 result=0;
 if(registered==1 && reachable==1)result=1;
 frame_placement_set_valid_palette(result);
 return result;
}

asm(".align 2,0");
