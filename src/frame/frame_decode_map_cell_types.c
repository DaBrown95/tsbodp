#include "frame_map_scene.h"
void frame_decode_map_cell_types(const void *data,const void *types) {unsigned int *bytes=&g_frame_map_cell_data_bytes;*bytes=resource_decode_bytes(data,g_frame_map_cell_data);g_frame_map_cell_count=(resource_decode_bytes(types,g_frame_map_cell_types)-4)>>1;g_frame_map_cell_header=*(unsigned short *)g_frame_map_cell_types;}
asm(".align 2,0");
