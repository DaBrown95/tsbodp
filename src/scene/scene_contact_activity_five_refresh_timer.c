#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_refresh_timer(int kind)
{
 int timer;
 switch(kind) {
 case 1:timer=frame_random_range(80,120);break;
 case 2:timer=frame_random_range(60,90);break;
 case 0:
 case 3:
 case 4:timer=frame_random_range(40,65);break;
 default:timer=0;break;
 }
 scene_contact_activity_five_assign_timer(kind,timer);
}
asm(".align 2, 0");
