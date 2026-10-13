#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_search.h"
void *scene_fill_bytes(void *,int,unsigned int);
extern unsigned char g_frame_search_neighbor_offsets[];
unsigned char frame_grid_search(void *context,const struct FrameActorPackedCell *start,const struct FrameActorPackedCell *target,unsigned int limit,unsigned char build_path)
{
 union FrameSearchWorkingRecord current,next;
 unsigned int i,iterations,found;
 unsigned int queue_index=0,empty=0;
 struct FrameSearchQueue *queue=g_frame_search_queues;
 struct FrameSearchNode **buffers=g_frame_search_node_buffers;
 {
 for(;queue_index<2;queue_index++){
  unsigned int offset=queue_index*4;
  struct FrameSearchNode *free_head=(struct FrameSearchNode *)frame_pool_initialize(*buffers++,300,24);
  *(struct FrameSearchNode **)((unsigned char *)g_frame_search_free_nodes+offset)=free_head;
  queue->first=empty;queue->last=empty;queue++;
}
 }
 g_frame_grid_search.target.axes.x=0;
 g_frame_grid_search.target.axes.y=0;
 scene_fill_bytes(g_frame_grid_search.cells,({register int clear_value asm("r1")=0;clear_value;}),400);
 g_frame_grid_search.context=context;
 g_frame_grid_search.target.word=*(const unsigned int *)target;
 g_frame_grid_search.status=0;
 {register unsigned int saved_mask asm("r7")=0xffff;
 if(start->index==target->index){
  g_frame_grid_search.cells[0]=*(const unsigned int *)start;
  g_frame_grid_search.count=1;
  return 2;
 }
 if(frame_search_cell_cost((const int *)target)>99){g_frame_grid_search.status=3;return 0;}
 current.fields.cell.word=*(const unsigned int *)start;
 current.fields.parent.axes.x=0;
 current.fields.parent.axes.y=0;
 frame_search_score(&current.record,0);
 if(!frame_search_append(&current.record,0)){g_frame_grid_search.status=2;return 0;}
 found=0;iterations=0;
 {unsigned int mask=saved_mask;
 while(frame_pool_count(&g_frame_search_queues[0])){
  iterations++;
  if(iterations>1000)return 0;
  frame_search_take_minimum(&current.record,0);
  {
   register unsigned int value asm("r0")=current.fields.cell.halfwords.index;
   struct FrameGridSearchState *state=&g_frame_grid_search;
   unsigned short target_value=(unsigned short)state->target.word;
   unsigned int left=mask;
   register unsigned int right asm("r0");
   left&=value;right=mask;right&=target_value;
  if(left==right){
   struct FrameSearchNode *node=frame_search_append(&current.record,0);
   found=1;
   if(!node){found=0;g_frame_grid_search.status=2;}
   goto complete;
  }
  if(current.fields.cost>limit){
   found=0;
   if(current.fields.cost>99){unsigned char *status=&state->status;*status=1;}
   else g_frame_grid_search.status=2;
   goto complete;
  }
  }
  for(i=0;i<4;i++){
   struct FrameSearchNode *existing;
   unsigned char *offsets=g_frame_search_neighbor_offsets;
   register unsigned char *entry asm("r1")=(unsigned char *)(i*4+(unsigned int)offsets);
   {unsigned int dx;next.fields.cell.axes.x=(dx=entry[0],dx+current.fields.cell.axes.x);}
   next.fields.cell.axes.y=current.fields.cell.axes.y+entry[1];
   next.fields.cost=current.fields.cost+frame_search_cell_cost((const int *)&next.fields.cell.word);
   frame_search_score(&next.record,next.fields.cost);
   {
    unsigned short next_key=next.fields.cell.halfwords.index;
    unsigned short parent_key=current.fields.parent.halfwords.index;
    register unsigned int left asm("r1")=mask;
    register unsigned int right asm("r0");
    left&=next_key;right=mask;right&=parent_key;
    if(left==right)continue;
   }
   existing=frame_search_find(&next.fields.cell.word,0);
   if(existing){
    if(existing->record.priority<=next.fields.priority)continue;
    frame_search_remove_cell(&next.fields.cell.word,0);
   }else{
    existing=frame_search_find(&next.fields.cell.word,1);
    if(existing){
     if(existing->record.priority<=next.fields.priority)continue;
     frame_search_remove_cell(&next.fields.cell.word,1);
    }
   }
   next.fields.parent.word=current.fields.cell.word;
   if(next.fields.cost<=99)existing=frame_search_append(&next.record,0);
   else existing=frame_search_append(&next.record,1);
   if(!existing){g_frame_grid_search.status=2;found=0;goto close_current;}
  }
  close_current:
  if(!frame_search_append(&current.record,1)){g_frame_grid_search.status=2;found=0;goto complete;}
 }
 }
 }
 complete:
 if(current.fields.priority>99){g_frame_grid_search.status=1;found=0;}
 {
  unsigned int okay=1;
  if(found==1){if(build_path==1)okay=frame_search_build_path(frame_search_find_any(&current.fields.cell.word));}
  else if(build_path==1&&g_frame_grid_search.status==2)okay=frame_search_build_path(frame_search_find_any(&current.fields.parent.word));
  if(!okay){g_frame_grid_search.status=1;found=0;}
 }
 return found;
}
