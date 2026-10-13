#include "frame_actor_runtime.h"
#include "frame_pool.h"
void *scene_fill_bytes(void *,int,unsigned int);
void frame_pool_push(struct FrameObjectList *list,struct FrameObject *object)
{
 struct FrameObject *first=list->first;
 object->next=first;
 object->previous=0;
 if(first)first->previous=object;
 list->first=object;
}
