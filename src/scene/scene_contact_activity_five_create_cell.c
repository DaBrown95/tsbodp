#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
struct FrameObject *scene_contact_activity_five_create_cell(unsigned int subtype,int x,int y)
{
 struct SceneContactActivityFiveObject *object=(struct SceneContactActivityFiveObject *)frame_allocate_object(1);
 object->subtype=subtype;
 frame_set_position((struct FrameObject *)object,x<<16,y<<16);
 object->contact_mode=0;
 object->double_size=0;
 object->layer=1;
 object->flags=0x819;
 frame_set_subtype_object_palette((struct FrameObject *)object,g_scene_contact_activity_five_cell_palettes);
 scene_contact_activity_five_set_cell_frame((struct FrameObject *)object);
 object->on_step=scene_contact_activity_five_step_cell;
 object->phase=0;
 object->destination=object->position;
 return (struct FrameObject *)object;
}
