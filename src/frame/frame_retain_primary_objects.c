#include "frame.h"
#include "scene_retention.h"
void frame_retain_primary_objects(void)
{
 struct FrameObject *object=g_frame_primary_list.first;
 while(object){frame_release_display(object);frame_enable_object_flags(object,0x02000000);object=object->next;}
 g_frame_retained_primary_list.first=g_frame_primary_list.first;
 g_frame_retained_primary_list.last=g_frame_primary_list.last;
 g_frame_primary_list.first=0;g_frame_primary_list.last=0;
}
