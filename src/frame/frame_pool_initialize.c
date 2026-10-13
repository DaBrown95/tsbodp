#include "frame_search.h"
void *scene_fill_bytes(void *,int,unsigned int);
struct FrameObject *frame_pool_initialize(void *memory,unsigned int count,unsigned int stride)
{
 struct FrameObject *first;
 unsigned int i;
 scene_fill_bytes(memory,0,count*stride);
 first=0;
 for(i=0;i<count;i++){
  frame_pool_push((struct FrameObjectList *)&first,(struct FrameObject *)memory);
  memory=(unsigned char *)memory+stride;
 }
 return first;
}
