#include "frame_map.h"
#include "input.h"
void frame_release_map_resources(void) {
 unsigned int i;
 struct FrameMapStore *store;
 for(i=0;i<2;i++) {
  struct FrameMapRecord *record=&g_frame_map_records[i];
  if(record->combined) heap_free(record->combined);
  if(record->secondary) heap_free(record->secondary);
  if(record->primary) heap_free(record->primary);
 }
 store=(struct FrameMapStore *)((unsigned char *)g_frame_map_records-4);
 if(store->default_resource) {
  heap_free(store->default_resource);
  store->default_resource=0;
 }
 heap_clear(store, 0, 0x1204);
 if(!(g_frame_flags & 0x20000))
  frame_set_view_origin(&g_frame_default_view_origin,g_input_config.local_player);
}
asm(".align 2, 0");
