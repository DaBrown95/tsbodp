#include "frame_search.h"
void frame_search_remove_cell(const unsigned int *cell_input,unsigned int queue)
{
 const unsigned int *cell=cell_input;
 struct FrameSearchNode *node=g_frame_search_queues[queue].first;
 if(node){
 unsigned int mask=0xffff;
 do{
  struct FrameSearchNode *next=node->next;
  unsigned short loaded_value=*(unsigned short *)&node->record.cell;
  unsigned int value=loaded_value;
  unsigned short loaded_key=*(unsigned short *)cell;
  unsigned int key=loaded_key;
  register unsigned int left asm("r1")=mask;
  register unsigned int right asm("r0");
  left&=value;
  right=mask;
  right&=key;
  if(left==right){
   unsigned int owner_queue=node->record.queue;
   if(g_frame_search_queues[owner_queue].last==node)g_frame_search_queues[owner_queue].last=node->previous;
   frame_pool_release(&g_frame_search_free_nodes[owner_queue],(struct FrameObjectList *)&g_frame_search_queues[owner_queue],(struct FrameObject *)node);
  }
  node=next;
 }while(node);
 }
}
