#include "frame_node_pool_1dac4.h"

void frame_initialize_node_pool_1dac4(void)
{
    heap_clear(&g_frame_node_pool_1dac4, 0, sizeof g_frame_node_pool_1dac4);
    g_frame_node_pool_1dac4.memory = heap_allocate(4608);
    g_frame_node_pool_1dac4.lists.heads.free_head = frame_pool_initialize(
        g_frame_node_pool_1dac4.memory, 128, 36);
}
