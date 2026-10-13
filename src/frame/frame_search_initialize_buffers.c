#include "frame_search.h"
#include "heap.h"
void frame_search_initialize_buffers(void)
{
 unsigned int i=0,empty=0;
 struct FrameSearchQueue *queue=g_frame_search_queues;
 struct FrameSearchNode **buffers=g_frame_search_node_buffers;
 for(;i<2;i++){
  struct FrameSearchNode *buffer=heap_allocate_zeroed(7200);
  unsigned int offset=i*4;
  struct FrameSearchNode *head;
  *buffers++=buffer;
  head=(struct FrameSearchNode *)frame_pool_initialize(buffer,300,24);
  *(struct FrameSearchNode **)((unsigned char *)g_frame_search_free_nodes+offset)=head;
  queue->first=empty;queue->last=empty;queue++;
 }
 g_frame_grid_search.target.axes.x=0;
 g_frame_grid_search.target.axes.y=0;
}
