#include "heap.h"
#include "frame_map_scene.h"

void frame_initialize_map_cell_buffers(void)
{
    g_frame_map_extra_decode = heap_allocate(0x2000);
    g_frame_map_cell_types = heap_allocate(0x2800);
    g_frame_map_cell_data = heap_allocate(0x4000);
    g_frame_map_extra_cell_types = g_frame_map_cell_types + 4;
}
