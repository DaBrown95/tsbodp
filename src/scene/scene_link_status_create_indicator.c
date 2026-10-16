#include "scene_link_status_private.h"
void scene_link_status_create_indicator(unsigned int index)
{
 struct FrameObject *object=frame_allocate_object(24);
 object->flags=17;
 object->unknown_0a=index;
 object->display_palette=index;
 object->display_layer=0;
 frame_set_position(object,g_link_status_indicator_resources[index].x<<16,g_link_status_indicator_resources[index].y<<16);
 frame_set_animation_record(object,&g_link_status_indicator_resources[index].animation);
 g_link_status_indicators[index]=object;
 object->flags&=~1u;
}
asm(".align 2,0");
