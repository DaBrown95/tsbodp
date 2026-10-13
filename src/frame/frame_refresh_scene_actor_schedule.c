#include "frame_grid_selection.h"
void frame_refresh_scene_actor_schedule(unsigned int world,const struct DisplayTimeRecord *clock)
{
 if(g_frame_scene_actor_eligibility_enabled) {
  g_frame_scene_actor_schedule_timer--;
  if(g_frame_scene_actor_schedule_timer==-1) {
   unsigned char id=18;
   struct FrameObject *object;
   struct FramePoint exit;
   struct FrameObject *marker;
   do {
    unsigned char allowed;
    if(id==31 && condition_is_complete(4,4,2)==1)goto next;
    allowed=frame_scene_actor_allowed(id,world,clock);
    if(allowed!=g_frame_scene_actor_presence[id-18]) {
     if(allowed==0) {
      if(frame_find_objects(7,id,&object,1)==1) {
       if(!(object->flags&0x800000)) {
        if(frame_scene_actor_find_exit(object,&exit)==1) {
         object->destination=exit;
         frame_enable_object_flags(object,0x800000);
        }
        goto reset;
       }
      }
     } else {
      if(frame_find_objects(15,0,&marker,1)==1 && frame_count_free_object_palettes()) {
       object=frame_create_actor(id,4,marker->position.x,marker->position.y);
       goto reset;
      }
     }
    }
next:
    id++;
   }while(id<=41);
reset:
   g_frame_scene_actor_schedule_timer=300;
  }
 }
}
asm(".align 2,0");
