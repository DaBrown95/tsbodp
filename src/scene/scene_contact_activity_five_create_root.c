#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
struct FrameObject *scene_contact_activity_five_create_root(void)
{
 struct SceneContactActivityFiveObject *object=(struct SceneContactActivityFiveObject *)frame_allocate_object(0);
 frame_set_position((struct FrameObject *)object,(STATE->selected_column<<20)+0x380000,(STATE->selected_row<<20)+0x140000);
 object->contact_mode=0;
 object->double_size=0;
 object->layer=0;
 object->palette=0;
 object->flags=25;
 frame_set_animation_record((struct FrameObject *)object,&g_scene_contact_activity_five_root_animation);
 object->on_step=scene_contact_activity_five_step_root;
 return (struct FrameObject *)object;
}
