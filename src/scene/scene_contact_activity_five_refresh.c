#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_refresh(void)
{
 int i;
 for(i=0;i<5;++i) {
  if(--STATE->timed[i].timer==-1) {
   if(frame_random_bounded(2))scene_contact_activity_five_set_timer(i,4);
   else scene_contact_activity_five_refresh_timer(i);
  }
 }
}
asm(".align 2, 0");
