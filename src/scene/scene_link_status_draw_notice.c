#include "scene_link_status_private.h"
void scene_link_status_draw_notice(unsigned int index)
{
 const struct SceneLinkStatusNotice *table_base=g_link_status_notices;
 const struct SceneLinkStatusNotice *notice=table_base+index;
 unsigned int text=notice->text;
 if(g_scene_request.scene!=text){
  if(g_scene_request.unknown_14==0){
   display_fill_background_constant_rectangle(0,5,16,20,4,0);
   display_text_select_font(3,0,0);
   display_text_draw_line(57,120,134,display_scene_lookup_text(text),1);
   g_scene_request.unknown_14=notice->delay;
   g_scene_request.scene=text;
  }else g_scene_request.unknown_14--;
 }
 if(g_scene_request.parameter){
  display_fill_background_constant_rectangle(0,5,13,20,2,0);
  display_text_select_font(3,0,0);
  display_text_draw_line(137,120,104,(const char*)g_scene_request.parameter,1);
  g_scene_request.parameter=0;
 }
}
asm(".align 2,0");
