#include "frame.h"
#include "scene_catalog.h"
void scene_catalog_selection(void) {
 unsigned int selector=g_scene_catalog_state.selector;
 if(selector==4) {
  if(g_scene_request.scene<g_scene_catalog_action_row) {
   if(g_display_scene_frame_objects[0]->unknown_0a==10) {
    g_display_scene_frame_objects[0]->unknown_0a=12;
    display_scene_refresh_item(g_display_scene_frame_objects[0]);
    g_scene_request.scene=selector;
   }
   g_display_scene_frame_objects[0]->id=g_scene_request.scene+123;
   frame_set_variant_state(g_display_scene_frame_objects[0],58);
  } else {
   if(g_display_scene_frame_objects[0]->unknown_0a==12) {
    g_display_scene_frame_objects[0]->unknown_0a=10;
    display_scene_refresh_item(g_display_scene_frame_objects[0]);
    g_scene_request.scene=g_scene_catalog_action_row;
   }
   g_display_scene_frame_objects[0]->id=g_scene_request.scene+38;
   frame_set_variant_state(g_display_scene_frame_objects[0],58);
  }
  scene_catalog_fill_original(g_scene_catalog_state.page_start,g_scene_catalog_state.row);
  scene_catalog_draw_original(g_scene_catalog_state.page_start,g_scene_catalog_state.row);
 } else {
  g_display_scene_frame_objects[0]->id=g_scene_request.scene+39;
  frame_set_variant_state(g_display_scene_frame_objects[0],58);
  scene_catalog_fill_original(g_scene_catalog_state.page_start,g_scene_catalog_state.row);
  scene_catalog_draw_original(g_scene_catalog_state.page_start,g_scene_catalog_state.row);
 }
}
asm(".align 2,0");
