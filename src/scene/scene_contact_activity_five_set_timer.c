#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_set_timer(int kind,unsigned int frame)
{
 int i;
 STATE->timed[kind].timer=frame_random_range(40,70);
 for(i=0;i<64;++i) {
  struct SceneContactActivityFiveObject *object=STATE->objects[i];
  if(object&&object->subtype==kind)object->frame=frame;
 }
}
asm(".align 2, 0");
