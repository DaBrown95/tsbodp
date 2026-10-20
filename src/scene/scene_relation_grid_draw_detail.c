#include "scene_relation_grid.h"
void scene_relation_grid_draw_detail(void)
{
 unsigned int limit=0x7fffffff;
 unsigned int entry;
 display_fill_background_constant_rectangle(0,13,11,15,9,0);
 display_fill_background_constant_rectangle(0,27,5,3,2,0);
 entry=g_scene_request.scene+g_scene_request.parameter;
 if(g_scene_request.scene>2)entry+=9;
 entry=g_scene_relation_grid_indices[entry];
 if(entry<=23 && display_menu_relation_initialized(&g_display_menu_relation_values,entry)){
  const char *text;
  unsigned int tile;
  int y;
  struct SceneRelationGridTextPoint point;
  display_text_select_font(3,0,0);
  display_text_draw_line(1,158,92,display_scene_lookup_text(entry+6025),1);
  display_clear_background_rectangle(0,13,13,16,7);
  display_text_select_font(1,0,-1);
  text=display_scene_lookup_text(entry+6049);
  y=108;tile=361;
  while(*text){tile=display_text_draw(tile,110,y,110,&text,0,&limit);y+=9;}
  point.x=238;point.y=45;
  scene_relation_grid_draw_relation(g_display_scene_frame_objects[6],211,point,entry);
  g_display_scene_frame_objects[6]->flags|=1;
 }else g_display_scene_frame_objects[6]->flags&=~1u;
}
asm(".align 2,0");
