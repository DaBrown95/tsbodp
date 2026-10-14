#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_begin_end(void)
{
 int sum=0,reward=0,i;
 for(i=8-STATE->column_count;i<8;++i)sum+=STATE->column_heights[i];
 if(sum<=2) {
  reward=g_scene_contact_activity_five_rows[STATE->option].reward;
  {register int limit asm("r0")=2-sum;
   if(limit>0) {
    register int remaining asm("r1")=limit;
    do {reward<<=1;}while(--remaining);
   }
  }
 }
 STATE->score+=reward;
 if(sum==0)audio_select_sequence(39);
 else if(sum>2)audio_select_sequence(37);
 else audio_select_sequence(38);
}
asm(".align 2, 0");
