#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_set_cell_timer(int row,int column,unsigned char delay)
{
 int cell=row+column*8,i=0;

 do {
  struct SceneContactActivityFiveObject *object=STATE->objects[i];
  if(object&&object->cell==cell) {object->timer=delay*8+1;break;}
 }while(++i<64);
}
