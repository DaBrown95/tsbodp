#include "frame_map.h"
void frame_load_combined_map_resource(unsigned int index, const void *primary, const void *secondary) {
 struct FrameMapRecord *record=&g_frame_map_records[index];
 if (!record->combined) {
  unsigned int bytes=resource_decoded_size(primary);
  if (secondary) bytes+=resource_decoded_size(secondary);
  record->combined=heap_allocate(bytes);
  if (secondary) resource_decode_bytes(secondary, (unsigned char *)record->combined+resource_decoded_size(primary)-4);
  resource_decode_bytes(primary, record->combined);
 }
}
asm(".align 2, 0");
