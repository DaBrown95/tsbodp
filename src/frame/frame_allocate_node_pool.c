#include "frame_node_pool.h"

struct FrameObject *frame_allocate_node_pool(void)
{
    return frame_pool_allocate(&g_frame_node_pool_1dac4.lists.heads.free_head,
                                        &g_frame_node_pool_1dac4.lists.active, 36);
}
