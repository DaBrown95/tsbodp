#include "scene_record_selection_panel.h"
void scene_record_selection_draw_panel(void)
{
 struct SaveStreamRecord *record = &g_save_stream_state.records[g_scene_request.parameter];
 unsigned int destination_x;
 int offset, pixel_x;
 unsigned short palette;
 const char *text;
 char formatted[32];
 if (SCENE_RECORD_SELECTION_STATE->unknown_0c[0] == 0) {
  destination_x = 3;
  offset = 24;
 } else {
  destination_x = 35;
  offset = 280;
 }
 palette = SCENE_RECORD_SELECTION_STATE->enabled[g_scene_request.parameter] ? 3 : 4;
 display_write_background_map(1,
     g_display_background_system.backgrounds[1].map_storage.map_pointer,
     1,palette,destination_x,3);
 display_text_set_background_control(g_scene_record_selection_control1);
 display_text_select_font(1,12,-1);
 if (SCENE_RECORD_SELECTION_STATE->occupied[g_scene_request.parameter])
  text = (const char *)record->unknown10;
 else
  text = display_scene_lookup_text(241);
 display_text_copy_field_one(text);
 if (g_scene_request.parameter != 3) {
  display_text_number_field_zero((int)(g_scene_request.parameter+1));
  text = display_scene_lookup_text(246);
 } else text = display_scene_lookup_text(247);
 pixel_x = offset+70;
 display_text_render(78,pixel_x,29,text);
 if (SCENE_RECORD_SELECTION_STATE->occupied[g_scene_request.parameter]) {
  display_text_number_field_zero(record->clock_storage.time.day+1);
  display_time_format(&record->clock_storage.time,formatted,6225);
  display_text_copy_field_one(formatted);
  display_text_render(118,pixel_x,56,display_scene_lookup_text(249));
  display_text_number_field_zero(record->signed24);
  display_text_render(158,pixel_x,72,display_scene_lookup_text(251));
 }
}
