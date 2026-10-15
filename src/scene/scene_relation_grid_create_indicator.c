#include "scene_relation_grid.h"
struct FrameObject *scene_relation_grid_create_indicator(unsigned int frame,unsigned int x,unsigned int y)
{
 struct FrameObject *object=frame_allocate_object(24);
 object->unknown_0a=frame;
 object->flags|=1;
 object->display_palette=6;
 object->display_layer=0;
 frame_set_animation_record(object,&g_scene_relation_grid_indicator_animation);
 frame_set_animation_frame((struct FrameTickObject *)object,(unsigned char)frame);
 frame_set_position(object,(int)(x<<16),(int)(y<<16));
 return object;
}
asm(".align 2,0");
