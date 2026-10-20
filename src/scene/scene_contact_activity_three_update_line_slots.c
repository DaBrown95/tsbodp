#include "scene_contact_activity_three.h"
#define LINE (&g_scene_contact_activity_three_slots)
extern struct FrameVariantResource g_scene_contact_activity_three_line_animation;
void scene_contact_activity_three_update_line_slots(void)
{
 int horizontal_step=0,x,y;
 unsigned int index;
 if(LINE->horizontal){
  int step_x=LINE->step.x;
  horizontal_step=-16;if(step_x>0)horizontal_step=16;
  x=(unsigned int)LINE->objects[0]->next_position.word.x+((unsigned int)horizontal_step<<16);
  y=(unsigned int)LINE->objects[0]->next_position.word.y-(unsigned int)LINE->delta.y;
 }else{
  x=(unsigned int)LINE->objects[0]->next_position.word.x-(unsigned int)LINE->delta.x;
  y=(unsigned int)LINE->objects[0]->next_position.word.y+16*65536u;
 }
 for(index=1;index<LINE->count;++index){
  struct FrameObject *object=LINE->objects[index];unsigned int tile;
  if(object==0){
   object=frame_allocate_object(6);object->flags=9;
   frame_set_animation_record(object,&g_scene_contact_activity_three_line_animation);
   ((struct SceneContactActivityThreeObject*)object)->contact_mode=0;
   ((struct SceneContactActivityThreeObject*)object)->double_size=0;
   ((struct SceneContactActivityThreeObject*)object)->layer=0;
   ((struct SceneContactActivityThreeObject*)object)->palette=14;
   LINE->objects[index]=object;
  }
  object->flags|=1;
  if(index==LINE->count-1)frame_set_position(object,(unsigned int)LINE->endpoint.x<<16,(unsigned int)LINE->endpoint.y<<16);
  else frame_set_position(object,x,y);
  tile=object->display_index;
  if(tile!=65535){
   display_cpu_copy((const void*)(0x06010000u+((unsigned int)LINE->objects[0]->display_index<<5)),(void*)(0x06010000u+(tile<<5)),0x04000020);
  }
  if(LINE->horizontal){
   y=(unsigned int)object->position.y-(unsigned int)LINE->delta.y;
   x=(unsigned int)object->position.x+((unsigned int)horizontal_step<<16);
  }else{
   x=(unsigned int)object->position.x-(unsigned int)LINE->delta.x;
   y=(unsigned int)object->position.y+16*65536u;
  }
 }
 if(LINE->count){
  for(index=LINE->count;index<16;++index){
   if(LINE->objects[index])LINE->objects[index]->flags&=~1u;
  }
 }
}
__asm__(".align 2,0");
