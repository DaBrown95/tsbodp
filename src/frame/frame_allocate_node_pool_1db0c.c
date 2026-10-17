#include "frame_node_pool_1dac4.h"

struct FrameObject *frame_allocate_node_pool_1db0c(void)
{
    return frame_pool_allocate_08024d50(
        &g_frame_node_pool_1dac4.lists.heads.free_head,
        &g_frame_node_pool_1dac4.lists.active, 36);
}
