#include "frame_search.h"
struct FrameSearchNode *frame_search_find(const unsigned int *cell,unsigned int queue)
{
 struct FrameSearchNode *node=g_frame_search_queues[queue].first;
 while(node){
  struct FrameSearchNode *next=node->next;
  register unsigned int value asm("r1")=*(unsigned short *)&node->record.cell;
  if((value&0xffff)==*(unsigned short *)cell)return node;
  node=next;
 }
 return 0;
}

asm(".align 2, 0");
