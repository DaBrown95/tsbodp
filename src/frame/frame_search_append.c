#include "frame_search.h"
struct FrameSearchNode *frame_search_append(const struct FrameSearchRecord *record,unsigned int queue)
{
 struct FrameSearchNode *node=(struct FrameSearchNode *)frame_pool_allocate_08024d50(&g_frame_search_free_nodes[queue],(struct FrameObjectList *)&g_frame_search_queues[queue],24);
 if(node){
  if(!g_frame_search_queues[queue].last)g_frame_search_queues[queue].last=node;
  node->record=*record;
  node->record.queue=queue;
 }
 return node;
}
