#include "frame_scene_player.h"
unsigned char frame_scene_read_spawn(unsigned char index,unsigned char *direction,int *x,int *y) {
 struct FrameSceneSpawnObject *object=g_frame_scene_spawn_list.first;
 while(object) {
  struct FrameSceneSpawnObject *next=object->next;
  if(object->id==18 && object->subtype==index) {
   if(direction)*direction=object->direction;
   *x=object->position.x;
   *y=object->position.y;
   return 1;
  }
  object=next;
 }
 return 0;
}
asm(".align 2,0");
