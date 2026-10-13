#include "frame_map_scene.h"
void frame_decode_extra_map_cell_types(const void *data,const void *types) {unsigned int bytes;resource_decode_bytes(data,g_frame_map_cell_data+g_frame_map_cell_data_bytes);bytes=resource_decode_bytes(types,g_frame_map_extra_decode);FRAME_MAP_DMA3->source=g_frame_map_extra_decode+4;FRAME_MAP_DMA3->destination=g_frame_map_extra_cell_types+(g_frame_map_cell_count<<1);FRAME_MAP_DMA3->control=0x80000000|((bytes-4)>>1);(void)FRAME_MAP_DMA3->control;}
asm(".align 2,0");
