#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
static inline void clear_shift(int index){STATE->pending_column_shifts[index]=0;}
unsigned char scene_contact_activity_five_advance(void)
{
 int cursor=STATE->settle_row;
 if(cursor<-1) {
  int i;
  if(!scene_contact_activity_five_selection_finished())return 0;
  scene_contact_activity_five_rebuild_cells();
  for(i=0;i<8;++i)clear_shift(i);
  g_scene_request.unknown_14=0;
  STATE->settle_row=7;
  return 1;
 }
 if(cursor<0) {
  if(!scene_contact_activity_five_selection_finished())return 0;
  scene_contact_activity_five_rebuild_cells();
  scene_contact_activity_five_compact_columns();
  --STATE->settle_row;
  return 0;
 }
 {unsigned int remaining=g_scene_request.unknown_14;
 unsigned int timer=remaining;
 --remaining;
 g_scene_request.unknown_14=remaining;
 if(timer==0) {
  int again=1;
  do {
   int i;
   g_scene_request.unknown_14=4;
   for(i=0;i<8;++i) {
    if(!STATE->cells.rows[i][STATE->settle_row])++STATE->pending_column_shifts[i];
    else if(STATE->pending_column_shifts[i]) {
     int cell=i+STATE->settle_row*8;
     struct SceneContactActivityFiveObject *object;
     again=0;
     object=(struct SceneContactActivityFiveObject *)g_frame_primary_list.last;
     while(object) {
      struct SceneContactActivityFiveObject *previous=object->previous;
      if(object->id==1&&object->cell==cell) {
       object->phase=14;
       object->acceleration.y=0x10000;
       object->destination.y=object->position.y+(STATE->pending_column_shifts[i]<<20);
      }
      object=previous;
     }
    }
   }
   --STATE->settle_row;
  }while(again&&STATE->settle_row>=0);
 }
 }
 return 0;
}
asm(".align 2, 0");
