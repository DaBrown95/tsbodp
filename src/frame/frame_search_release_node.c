#include "frame_search.h"
unsigned int frame_search_release_node(struct FrameSearchNode *node)
{
 unsigned int queue=node->record.queue;
 if(g_frame_search_queues[queue].last==node)g_frame_search_queues[queue].last=node->previous;
 frame_pool_release(&g_frame_search_free_nodes[queue],(struct FrameObjectList *)&g_frame_search_queues[queue],(struct FrameObject *)node);
 return 1;
}
