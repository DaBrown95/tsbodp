#include "frame_map_scene.h"
void frame_load_scene_map_resources(unsigned int index) {
 struct FramePoint dimensions;
 const struct FrameMapSceneResource *resources=g_frame_map_scene_resources;
 const struct FrameMapSceneResource *resource=&resources[index];
 frame_configure_deferred_display(resource->deferred_layer);
 frame_set_map_sources(&g_scene_background_control2,&g_scene_background_control1);
 if(!g_scene_request.mode) {
  const struct FrameMapTileResource *tiles=g_frame_map_scene_resources[index].tile_resource;
  frame_load_selected_map_tiles(tiles,resource->selection0,(const struct FrameMapBackgroundControl *)&g_scene_background_control2);
  frame_load_selected_map_tiles(tiles,g_frame_map_scene_resources[index].selection1,(const struct FrameMapBackgroundControl *)&g_scene_background_control1);
  frame_load_map_resources(0,g_frame_map_scene_resources[index].primary0,g_frame_map_scene_resources[index].secondary0);
  frame_load_map_resources(1,g_frame_map_scene_resources[index].primary1,g_frame_map_scene_resources[index].secondary1);
  frame_decode_map_cell_types(g_frame_map_scene_resources[index].cell_data,g_frame_map_scene_resources[index].cell_types);
  if(g_frame_map_scene_resources[index].extra_cell_types)frame_decode_extra_map_cell_types(g_frame_map_scene_resources[index].extra_cell_data,g_frame_map_scene_resources[index].extra_cell_types);
  scene_stage_080301c4();
  frame_initialize_map_palette_slots();
  frame_get_map_dimensions(&dimensions);
  g_frame_registration=frame_create_map_registration((unsigned short)dimensions.x,(unsigned short)dimensions.y,16);
  resource_decode_bytes(g_frame_map_scene_resources[index].registration_data,((struct FrameMapRegistration *)g_frame_registration)->data);
 } else frame_restore_map_vram();
 frame_load_combined_map_resource(0,g_frame_map_scene_resources[index].combined0,g_frame_map_scene_resources[index].combined0_alternate);
 frame_load_combined_map_resource(1,g_frame_map_scene_resources[index].combined1,g_frame_map_scene_resources[index].combined1_alternate);
}
asm(".align 2,0");
