#include "scene_contact_activity_six.h"
#define STATE ((struct SceneContactActivitySixState *)g_scene_contact_state)
void scene_contact_activity_six_remove_finished(struct FrameObject *base) {
 if(base->position.y<=0)frame_enable_object_flags(base,2);
}
asm(".align 2,0");
