#include "scene_contact_activity_two.h"
struct FrameObject *scene_contact_activity_two_create_primary(void) {
 struct SceneContactActivityTwoObject *object=(void *)frame_allocate_scene_object();
 struct FrameVariantResource *resource;
 object->id=0;
 object->contact_mode=0;object->double_size=0;object->layer=2;object->palette=0;
 object->flags=17;
 frame_set_position((struct FrameObject *)object,0*65536,88*65536);
 resource=&g_scene_contact_activity_two_primary_animation;
 frame_set_animation_record((struct FrameObject *)object,resource);
 frame_set_animation_program((struct FrameObject *)object,(struct FrameSpriteResource *)resource,g_scene_contact_activity_two_primary_program,0);
 return (struct FrameObject *)object;
}
asm(".align 2, 0");
