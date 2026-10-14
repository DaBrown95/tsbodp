#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_rebuild_cells(void)
{
 int i;
 heap_clear(STATE->column_heights,0,8);
 heap_clear(STATE->cells.flat,0,64);
 for(i=0;i<64;++i) {
  struct SceneContactActivityFiveObject *object=STATE->objects[i];
  if(object) {
   int x=display_bios_div((short)(object->position.x>>16)-56,16);
   int y=display_bios_div((short)(object->position.y>>16)-20,16);
   object->cell=y*8+x;
   STATE->cells.rows[x][y]=(*(unsigned char *)&object->subtype)+((((*(unsigned char *)&object->subtype)+1)<<4)+1);
   ++STATE->column_heights[x];
  }
 }
}
