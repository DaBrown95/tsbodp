#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_reset_selection(void)
{
 int i,j;
 for(i=0;i<8;++i) {
  for(j=0;j<8;++j) {
   struct SceneContactActivityFiveObject *object=STATE->objects[i*8+j];
   unsigned int value=STATE->cells.flat[i*8+j]&15;
   STATE->cells.flat[i*8+j]=value|(value<<4);
   if(object) {
    object->contact_mode=0;
    if(!object->phase)object->timer=0;
   }
  }
 }
 STATE->selected_count=0;
}
