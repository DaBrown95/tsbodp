#include "scene_relation_grid.h"
void scene_relation_grid_initialize(void)
{
 unsigned char *world=g_scene_relation_grid_world.bytes;
 const unsigned char *palette;
 unsigned int control,tile,index;
 int baseline,icon_y,frame;
 g_scene_request.scene=0;
 g_scene_request.parameter=0;
 scene_relation_grid_sort_relations((const struct DisplayMenuRelationValues *)(world+0x20));
 display_set_mode(0);
 display_enable_layers(4096);
 display_show_background(3,g_scene_relation_grid_control3);
 display_show_background(2,g_scene_relation_grid_control2);
 display_show_background(1,g_scene_relation_grid_control1);
 display_fill_background(1,0);
 control=g_scene_relation_grid_control0;
 display_show_background(0,control);
 display_fill_background(0,0);
 display_text_set_background_control(control);
 palette=(const unsigned char *)&g_display_scrolling_palette+2;
 display_load_palette_alternate(palette,0,16);
 display_load_background(3,&g_scene_relation_grid_background3,0,4,0,0);
 display_set_background_velocity(3,32768,32768);
 display_load_background(2,&g_scene_relation_grid_background2,4,1,0,0);
 display_load_resource_palette((const struct BackgroundResource *)(palette-2),0);
 scene_relation_grid_create_objects();
 scene_relation_grid_draw_detail();
 scene_relation_grid_refresh_entries_original();
 display_text_select_font(3,0,0);
 display_text_copy_field_zero((const char *)world);
 display_text_draw_line(151,74,4,display_scene_lookup_text(6223),1);
 display_text_number_field_zero(display_menu_read_relation_average((struct DisplayMenuRelationState *)world));
 display_text_draw_line(91,172,4,display_scene_lookup_text(443),1);
 display_text_select_font(1,0,-1);
 display_text_draw_line(61,65,26,display_scene_lookup_text((unsigned char)scene_relation_grid_descriptor_original(world+0x18)+451),1);
 tile=221;
 display_text_select_font(1,0,-1);
 index=0;icon_y=48;baseline=47;
 for(;index<5;index++){
  tile=display_text_draw_line(tile,4,baseline,display_scene_lookup_text(index+463),0);
  frame=(unsigned char)scene_relation_grid_trait_original(world+0x18,index);
  display_load_palette_alternate(g_scene_relation_grid_icon_palette,96,16);
  scene_relation_grid_create_indicator(frame,64,icon_y);
  icon_y+=10;baseline+=10;
 }
 tile=281;index=0;
 world+=0x88;
 icon_y=99;baseline=98;
 for(;index<6;index++){
  tile=display_text_draw_line(tile,4,baseline,display_scene_lookup_text(index+265),0);
  frame=frame_read_signed_parameter(world,index);
  scene_relation_grid_create_indicator(frame,64,icon_y);
  icon_y+=10;baseline+=10;
 }
 transition_run_first(63,0);
}
asm(".align 2,0");
