#include "frame.h"
#include "scene_catalog_text.h"
void scene_catalog_update(void) {
 unsigned int color;
 display_text_select_font(3,0,0);
 display_fill_background_constant_rectangle(0,23,3,7,2,color=0);
 if(g_scene_request.scene>=g_scene_catalog_action_row) {
  unsigned int text;
  if(g_scene_request.mode==0) {
   if(g_scene_catalog_state.selector==13) {
    g_display_scene_frame_objects[10]->flags|=1;
    text=0x184b;
   } else text=0x1848;
  } else text=0x184a;
  display_text_draw_line(51,184,24,display_scene_lookup_text(text),0);
 } else {
  if(g_scene_catalog_state.selector==13)g_display_scene_frame_objects[10]->flags&=~1U;
  else display_text_draw_line(51,184,24,display_scene_lookup_text(0x1849),color);
 }
}
asm(".align 2,0");
