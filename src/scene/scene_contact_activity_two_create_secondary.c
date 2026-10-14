#include "scene_contact_activity_two.h"
struct FrameObject *scene_contact_activity_two_create_secondary(void) {
 struct SceneContactActivityTwoObject *object=(void *)frame_allocate_scene_object();
 struct FrameVariantResource *resource;
 object->id=1;
 object->contact_mode=0;object->double_size=0;object->layer=2;object->palette=1;

 frame_set_position((struct FrameObject *)object,4*65536,156*65536);
 resource=&g_scene_contact_activity_two_secondary_animation;
 frame_set_animation_record((struct FrameObject *)object,resource);
 frame_set_animation_program((struct FrameObject *)object,(struct FrameSpriteResource *)resource,g_scene_contact_activity_two_secondary_program,0);
 return (struct FrameObject *)object;
}
asm(".align 2, 0");
