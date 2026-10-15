#include "scene_link_catalog.h"
void scene_link_catalog_draw_panel(unsigned int kind)
{
 const char *text;
 int width,row;
 unsigned int height,column,tile;
 switch(kind){
 case 0:g_scene_request.unknown_10=2;g_scene_request.parameter=1;text=display_scene_lookup_text(441);height=8;row=5;break;
 case 1:g_scene_request.unknown_10=9;text=display_scene_lookup_text(294);height=4;row=7;break;
 case 2:g_scene_request.unknown_10=9;text=display_scene_lookup_text(296);height=4;row=7;break;
 case 3:g_scene_request.unknown_10=9;text=display_scene_lookup_text(300);height=4;row=7;break;
 case 4:g_scene_request.unknown_10=9;text=display_scene_lookup_text(296);height=4;row=7;break;
 default:text=0;height=4;row=7;break;
 }
 width=(display_text_measure_width(text)+7)/8+3;
 column=30-width;
 column>>=1;
 display_text_select_font(3,0,-1);
 scene_view_load_fixed_resource(0,185,9);
 scene_view_draw_frame(column,row,width,height);
 display_text_set_background_control(g_scene_link_catalog_control0);
 if(kind==0){
  text=display_scene_lookup_text(440);
  tile=display_text_draw_line(194,120,(row+1)*8,text,1);
  display_text_draw_line(tile,120,(row+1)*8+12,display_scene_lookup_text(441),1);
 }else display_text_draw_line(194,120,(row+1)*8,text,1);
}
asm(".align 2,0");
