#include "frame_search.h"
void *scene_fill_bytes(void *,int,unsigned int);
void frame_search_reset(void)
{
 unsigned int i=0,empty=0;
 struct FrameSearchQueue *queue=g_frame_search_queues;
 struct FrameSearchNode **buffers=g_frame_search_node_buffers;
 for(;i<2;i++){
  unsigned int offset=i*4;
  struct FrameSearchNode *head=(struct FrameSearchNode *)frame_pool_initialize(*buffers++,300,24);
  *(struct FrameSearchNode **)((unsigned char *)g_frame_search_free_nodes+offset)=head;
  queue->first=empty;queue->last=empty;queue++;
 }
 g_frame_grid_search.target.axes.x=0;
 g_frame_grid_search.target.axes.y=0;
 scene_fill_bytes(g_frame_grid_search.cells,0,400);
}
