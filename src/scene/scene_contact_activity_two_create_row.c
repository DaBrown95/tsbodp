#include "scene_contact_activity_two.h"
struct FrameObject *scene_contact_activity_two_create_row(unsigned int index) {
 struct SceneContactActivityTwoRowObject *object=(void *)frame_allocate_scene_object();
 unsigned int id=index+3;
 object->id=id;object->subtype=index;
 object->contact_mode=0;object->double_size=0;object->layer=2;object->palette=id;
 object->flags=1;
 frame_set_position((struct FrameObject *)object,(unsigned int)g_scene_contact_activity_two_rows[index].x<<16,(unsigned int)g_scene_contact_activity_two_rows[index].y<<16);
 frame_set_animation_record((struct FrameObject *)object,&g_scene_contact_activity_two_rows[index].animation);
 display_load_palette_alternate(g_scene_contact_activity_two_rows[index].palette,id<<4,16);
 object->on_step=scene_contact_activity_two_step_row;
 object->phase=11;
 object->timer=frame_random_range(30,120);
 if(index>3)((unsigned char *)object)[0xd3]|=0x20;
 return (struct FrameObject *)object;
}
asm(".align 2, 0");
