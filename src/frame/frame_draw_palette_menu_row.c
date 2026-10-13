#include "frame_actor_palette_menu.h"
#include "display_text_draw.h"
void frame_draw_palette_menu_row(unsigned int row)
{
 const char *text;
 unsigned int enabled=g_frame_actor_palette_menu_enabled[row];
 unsigned int color=1;
 if(enabled)color=0;
 display_text_select_font(3,color,0);
 text=display_scene_lookup_text(row+24);
 if(row==5) {
  display_fill_background_constant_rectangle(0,3,12,16,2,0);
  if(g_frame_actor_palette_menu_choices[0]==1)text=display_scene_lookup_text(32);
 }
 display_text_draw_block(row*40+1,g_frame_actor_palette_menu_text_points[row].x,g_frame_actor_palette_menu_text_points[row].y,80,32,&text,1);
 if(row==0) {
  row=5;
  if(g_frame_actor_palette_menu_state.selectors[0]!=g_frame_actor_palette_menu_choices[0]) {
   if(g_frame_actor_palette_menu_choices[0]==1)text=display_scene_lookup_text(32);
   else text=display_scene_lookup_text(29);
   display_fill_background_constant_rectangle(0,6,12,6,2,0);
   display_text_draw_block(row*40+1,g_frame_actor_palette_menu_text_points[row].x,g_frame_actor_palette_menu_text_points[row].y,80,32,&text,1);
  }
 }
}
asm(".align 2, 0");
