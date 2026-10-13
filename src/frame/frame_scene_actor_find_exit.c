#include "frame_grid_selection.h"
unsigned char frame_scene_actor_find_exit(struct FrameObject *object,struct FramePoint *point)
{
 struct FrameObject *markers[5];
 unsigned char count=frame_find_objects(15,0,markers,5);
 if(!count)return 0;
 {
  unsigned int nearest=0x27100000;
  unsigned char selected=0;
  unsigned char i;
  for(i=0;i<count;i++) {
   unsigned int distance=view_point_distance(object->position,markers[i]->position);
   if(distance<nearest) {
    nearest=distance;
    selected=i;
   }
  }
  *point=markers[selected]->position;
  return 1;
 }

}
asm(".align 2,0");
