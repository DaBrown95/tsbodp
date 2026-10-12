#include "frame_map.h"
void frame_load_map_resources(unsigned int index, const void *primary, const void *secondary) {
 struct FrameMapRecord *record=&g_frame_map_records[index];
 if (!record->primary) {
  record->primary=heap_allocate(resource_decoded_size(primary));
  resource_decode_bytes(primary, record->primary);
  record->width=((unsigned short *)record->primary)[0];
  record->height=((unsigned short *)record->primary)[1];
 }
 if (!record->secondary && secondary) {
  record->secondary=heap_allocate(resource_decoded_size(secondary));
  resource_decode_bytes(secondary, record->secondary);
 }
}
asm(".align 2, 0");
