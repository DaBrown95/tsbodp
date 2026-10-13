#include "frame_actor_runtime.h"
#include "frame_pool.h"
void *scene_fill_bytes(void *,int,unsigned int);
void frame_pool_release(void *free_list,struct FrameObjectList *active_list,struct FrameObject *object)
{
 frame_pool_remove(active_list,object);
 frame_pool_push(free_list,object);
}
