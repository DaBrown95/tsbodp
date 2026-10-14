#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_assign_timer(int kind,int timer)
{
 int i;
 STATE->timed[kind].timer=timer;
 for(i=0;i<64;++i) {
  struct SceneContactActivityFiveObject *object=STATE->objects[i];
  if(object&&object->subtype==kind)scene_contact_activity_five_set_cell_frame((struct FrameObject *)object);
 }
}
asm(".align 2, 0");
