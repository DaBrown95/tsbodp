#include "frame_map.h"
#include "input.h"
void frame_snapshot_map_vram(void) {
 unsigned int index;
 struct FrameMapStore *store;
 void *snapshot;
 for(index=0;index<2;index++) {
  struct FrameMapRecord *record=&g_frame_map_records[index];
  if(record->combined) {
   heap_free(record->combined);
   record->combined=0;
  }
 }
 snapshot=heap_allocate(0xC000);
 store=(struct FrameMapStore *)((unsigned char *)g_frame_map_records-4);
 store->default_resource=snapshot;
 resource_bios_swi_0c((void*)0x06000000,store->default_resource,0x3000);
 frame_set_view_origin(&g_frame_default_view_origin,g_input_config.local_player);
}
asm(".align 2,0");
