#include "scene_palette_menu_selection_transition.h"
struct FrameObject *scene_palette_menu_create_selection_object(unsigned int id,unsigned int x,unsigned int y) {
 struct FrameObject *object=frame_allocate_object(24);
 object->unknown_0a=id;
 object->flags|=1;
 object->display_palette=6; object->display_layer=0;
 frame_set_animation_record(object,&g_palette_menu_selection_animation);
 frame_set_position(object,x<<16,y<<16);
 return object;
}
asm(".align 2,0");
