#include "scene_relation_grid.h"
void scene_relation_grid_create_objects(void)
{
 int index;
 g_display_scene_frame_objects[9]=frame_create_scene_object(95,10,1,1);
 g_display_scene_frame_objects[10]=frame_create_scene_object(104,236,2,1);
 g_display_scene_frame_objects[11]=frame_create_scene_object(105,237,2,1);
 g_display_scene_frame_objects[6]=frame_create_scene_object(101,8,3,1);
 g_display_scene_frame_objects[6]->flags&=~16u;
 g_display_scene_frame_objects[7]=frame_create_scene_object(102,270,4,1);
 g_display_scene_frame_objects[7]->flags&=~1u;
 g_display_scene_frame_objects[8]=frame_create_scene_object(103,271,4,1);
 for(index=5;index>=0;index--){
  unsigned int entry,subtype;
  if(index<=2)entry=g_scene_relation_grid_indices[index];
  else entry=g_scene_relation_grid_indices[index+9];
  if(display_menu_relation_initialized(&g_display_menu_relation_values,entry))subtype=entry+239;
  else subtype=226;
  g_display_scene_frame_objects[index]=frame_create_scene_object(index+95,subtype,index+7,1);
  g_display_scene_frame_objects[index]->flags&=~1u;
 }
}
asm(".align 2,0");
