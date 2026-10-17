#include "frame_node_pool_1dac4.h"

void frame_shutdown_node_pool_1daf0(void)
{
    heap_free(g_frame_node_pool_1dac4.memory);
    g_frame_node_pool_1dac4.memory = 0;
    g_frame_node_pool_1dac4.lists.heads.free_head = 0;
    g_frame_node_pool_1dac4.lists.heads.active_head = 0;
}
