#include "frame_actor_runtime.h"
#include "frame_pool.h"
void *scene_fill_bytes(void *,int,unsigned int);
struct FrameObject *frame_pool_allocate_08024d50(void *free_list,struct FrameObjectList *active_list,unsigned int bytes)
{
 if(!((struct FrameObjectList *)free_list)->first)return 0;
 {
  struct FrameObject *object=frame_pool_pop(free_list);
  scene_fill_bytes(object,0,bytes);
  frame_pool_push(active_list,object);
  return object;
 }
}
asm(".align 2, 0");
