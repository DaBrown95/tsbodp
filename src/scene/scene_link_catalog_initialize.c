#include "scene_link_catalog.h"
void scene_link_catalog_initialize(void)
{
 unsigned int control,tile;
 unsigned char i;
 unsigned char *quantities;
 g_scene_request.scene=5;
 switch(g_scene_request.mode) {
 case 2:
  g_scene_request.unknown_10=3;
  g_link_received_join.identifier=-1;
  g_link_received_join.metadata[0]=0;
  g_link_received_join.entry_index=0;
  audio_select_sequence(2);break;
 default:g_scene_request.unknown_10=0;break;
 case 1:g_scene_request.unknown_10=1;break;
 }
 display_set_mode(0);display_enable_layers(0x1000);
 display_show_background(3,g_scene_link_catalog_control3);
 display_show_background(2,g_scene_link_catalog_control2);
 control=g_scene_link_catalog_control1;
 display_show_background(1,control);display_fill_background(1,0);
 display_show_background(0,g_scene_link_catalog_control0);display_fill_background(0,0);
 display_text_set_background_control(control);
 display_load_background(3,&g_display_scrolling_resource3,1,4,0,0);
 display_set_background_velocity(3,0x8000,0x8000);
 display_load_background(2,&g_scene_link_catalog_background2,5,1,0,0);
 display_load_resource_palette(&g_display_scrolling_palette,0);
 display_text_select_font(3,0,0);
 display_text_draw_line(41,74,5,display_scene_lookup_text(442),1);
 display_text_select_font(1,0,0);
 tile=121;
 for(i=0,quantities=g_scene_catalog_quantities;i<=4;i++) {
  unsigned int quantity_address=i;
  quantity_address+=(unsigned int)quantities;
  display_text_number_field_zero(*(unsigned char *)quantity_address);
  tile=display_text_draw_line(tile,g_scene_link_catalog_captions[i].x,g_scene_link_catalog_captions[i].y,display_scene_lookup_text(0x184e),2);
 }
 display_text_select_font(3,0,0);
 display_text_number_field_zero(g_scene_link_catalog_world.value);
 display_text_draw_line(151,174,5,display_scene_lookup_text(0x184c),1);
 scene_link_catalog_build();display_catalog_draw_selection();
 if(g_frame_flags&0x20)transition_fade_black_in_record(63);
 else transition_run_first(63,0);
}
