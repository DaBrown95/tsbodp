#include "scene_contact_activity_five.h"
#define STATE ((struct SceneContactActivityFiveState *)g_scene_contact_state)
void scene_contact_activity_five_step_root(struct FrameObject *base)
{
 struct SceneContactActivityFiveObject *object=(struct SceneContactActivityFiveObject *)base;
 object->position.x=(STATE->selected_column<<20)+0x380000;
 object->position.y=(STATE->selected_row<<20)+0x140000;
}
asm(".align 2,0");
