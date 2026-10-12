#include "frame_map.h"
#include "input.h"
void frame_release_map_resources(void) {
 unsigned int i;
 struct FrameMapStore *store;
 for(i=0;i<2;i++) {
  struct FrameMapRecord *record=&g_frame_map_records[i];
  if(record->combined) frame_map_free_bytes(record->combined);
  if(record->secondary) frame_map_free_bytes(record->secondary);
  if(record->primary) frame_map_free_bytes(record->primary);
 }
 store=(struct FrameMapStore *)((unsigned char *)g_frame_map_records-4);
 if(store->default_resource) {
  frame_map_free_bytes(store->default_resource);
  store->default_resource=0;
 }
 frame_map_clear_bytes(store, 0, 0x1204);
 if(!(g_frame_flags & 0x20000))
  frame_set_view_origin(&g_frame_default_view_origin,g_input_config.local_player);
}
asm(".align 2, 0");
