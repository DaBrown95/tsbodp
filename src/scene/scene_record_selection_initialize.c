#include "scene_record_selection_setup.h"
void scene_record_selection_initialize(void)
{
 unsigned int control, index;
 const unsigned char *palette;
 const char *text;
 struct SaveStreamState *saved;
 register struct SaveStreamState *valid_state asm("ip");
 display_reset();
 display_set_mode(0);
 display_configure_tile_allocation(0);
 display_enable_layers(0x1000);
 display_show_background(3,g_scene_record_selection_control3);
 display_load_background(3,&g_scene_record_selection_background3,1,1,0,0);
 display_set_background_velocity(3,-65536,-65536);
 control=g_scene_record_selection_control2;
 display_show_background(2,control);
 display_fill_background(2,0);
 display_load_background(2,&g_scene_record_selection_background2a,18,2,4,0);
 display_load_background(2,&g_scene_record_selection_background2b,40,2,0,16);
 display_show_background(1,g_scene_record_selection_control1);
 display_fill_background(1,0);
 g_display_background_system.backgrounds[1].map_storage.map_pointer=
  display_load_background_resource(1,&g_scene_record_selection_background1,1,3);
 display_load_palette(g_scene_record_selection_palette1,64,16);
 display_show_background(0,g_scene_record_selection_control0);
 palette=(const unsigned char *)&g_scene_record_selection_palette;
 display_load_resource_palette((const struct BackgroundResource *)palette,0);
 display_fill_background(0,0);
 palette+=2;
 display_load_palette_alternate(palette,0,16);
 display_text_set_background_control(control);
 display_text_select_font(3,12,-1);
 text=display_scene_lookup_text(g_scene_record_selection_titles[g_scene_request.mode]);
 display_text_draw_line(57,120,5,text,1);
 display_text_draw_line(87,40,139,text,0);
 display_text_draw_line(117,144,139,display_scene_lookup_text(244),0);
 g_frame_actor_palette_scene_resource=heap_allocate_zeroed(16);
 index=0;
 saved=&g_save_stream_state;
 valid_state=saved;
 do {
  unsigned int valid_address = (unsigned int)valid_state->valid;
  if(*(unsigned char *)(index + valid_address) && saved->records[index].unknown10[0]) SCENE_RECORD_SELECTION_STATE->occupied[index]=1;
  else SCENE_RECORD_SELECTION_STATE->occupied[index]=0;
  if(g_scene_request.mode==0 ||
     (g_scene_link_catalog_world.unknown00==0 ? index<=2 : index==3))
   SCENE_RECORD_SELECTION_STATE->enabled[index]=1;
  ++index;
 } while(index<=3);
 g_scene_request.parameter=saved->selected;
 if(g_scene_request.mode==1) {
  if(g_scene_link_catalog_world.unknown00==0) {
   if(g_scene_request.parameter==3) g_scene_request.parameter=0;
  } else g_scene_request.parameter=3;
 }
 g_scene_request.unknown_10=1;
 frame_create_palette_scene_actor(0);
 scene_record_selection_create_objects();
 scene_record_selection_draw_panel_original();
 transition_run_first(63,0);
}

/* Preserve the native two zero alignment bytes after the return. */
asm(".align 2, 0");
