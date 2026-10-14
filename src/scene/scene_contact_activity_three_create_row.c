#include "scene_contact_activity_three.h"
#define STATE ((struct SceneContactActivityThreeState*)g_scene_contact_state)
struct FrameObject *scene_contact_activity_three_create_row(unsigned int palette) {
 struct FrameObject *base=frame_allocate_scene_object();struct SceneContactActivityThreeObject *object=(void*)base;struct FrameActorObject *actor=(void*)base;
 object->id=palette;
 scene_contact_activity_three_original_prepare_row(base);
 object->contact_mode=0;object->double_size=0;object->layer=3;object->palette=palette;object->flags=25;
 base->on_step=scene_contact_activity_three_step_row;
 actor->variant_state=1;
 scene_contact_activity_three_reset_row(base);
 ++STATE->active_rows;
 return base;
}
asm(".align 2,0");
