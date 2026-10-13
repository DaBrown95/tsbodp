#include "frame_actor_runtime.h"
#include "frame_pool.h"
void *scene_fill_bytes(void *,int,unsigned int);
struct FrameObject *frame_pool_pop(struct FrameObjectList *list)
{
 struct FrameObject *object=list->first;
 if(object) {
  struct FrameObject *next=object->next;
  list->first=next;
  if(next)next->previous=0;
  object->next=0;
 }
 return object;
}
asm(".align 2, 0");
