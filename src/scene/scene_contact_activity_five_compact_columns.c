#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_compact_columns(void)
{
 int count=0,i;
 for(i=0;i<8;++i)if(STATE->column_heights[i])++count;
 if(STATE->column_count!=count) {
  for(i=0;i<64;++i) {
   struct SceneContactActivityFiveObject *object=STATE->objects[i];
   if(object) {
    int x=(short)(object->position.x>>16),shift=0,j;
    for(j=8-STATE->column_count;j<8;++j) {
     if(!STATE->column_heights[j]&&j*16+56>x)++shift;
    }
    if(shift) {
     object->phase=14;
     object->acceleration.x=0x10000;
     object->destination.x=object->position.x+(shift<<20);
    }
   }
  }
  STATE->column_count=count;
 }
}
asm(".align 2, 0");
