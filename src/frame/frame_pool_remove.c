#include "frame_actor_runtime.h"
#include "frame_pool.h"
void *scene_fill_bytes(void *,int,unsigned int);
void frame_pool_remove(struct FrameObjectList *list,struct FrameObject *object)
{
 if(list->first==object)list->first=object->next;
 if(object->next)object->next->previous=object->previous;
 if(object->previous)object->previous->next=object->next;
 object->next=0;object->previous=0;
}
