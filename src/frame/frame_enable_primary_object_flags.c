#include "frame.h"
#include "scene_retention.h"
void frame_enable_primary_object_flags(unsigned int flags)
{
 struct FrameObject *object=g_frame_primary_list.first;
 while(object){object->flags|=flags;object=object->next;}
}
