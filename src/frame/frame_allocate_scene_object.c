#include "frame_scene_object.h"
struct FrameObject *frame_allocate_scene_object(void)
{
 struct FrameObject *object=frame_pool_allocate_08024d50(g_frame_object_pool,&g_frame_primary_list,320);
 if(object) {
  if(!g_frame_primary_list.last) g_frame_primary_list.last=object;
  object->id=65535;
  object->display_index=65535;
 }
 return object;
}
