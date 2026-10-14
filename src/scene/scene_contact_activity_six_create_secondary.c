#include "scene_contact_activity_six.h"
struct FrameObject *scene_contact_activity_six_create_secondary(void) {
 struct FrameActorObject *object=(void *)frame_allocate_scene_object();
 struct SceneContactActivitySixAppearance *appearance;
 frame_set_position((struct FrameObject *)object,122*65536,108*65536);
 object->direction=4;object->id=1;
 ((struct SceneContactActivitySixObject *)object)->contact_mode=0;
 ((struct SceneContactActivitySixObject *)object)->double_size=0;
 ((struct SceneContactActivitySixObject *)object)->layer=1;
 ((struct SceneContactActivitySixObject *)object)->secondary=1;
 frame_enable_object_flags((struct FrameObject *)object,25);
 object->on_step=scene_contact_activity_six_step_secondary;
 appearance=&g_scene_contact_activity_six_secondary_appearance;
 frame_load_actor_group_palette(appearance,1);
 frame_enable_parts((struct FrameObject *)object);
 frame_request_animation((struct FrameCommandObject *)object,0);
 frame_set_part_variants((struct FrameObject *)object,0,g_scene_contact_activity_six_part0_tables[appearance->group],1);
 frame_set_part_variants((struct FrameObject *)object,1,g_scene_contact_activity_six_part1_tables[appearance->group][appearance->variant],1);
 frame_set_part_variants((struct FrameObject *)object,2,g_scene_contact_activity_six_part2_tables[appearance->group],15);

 frame_set_animation_variant((struct FrameObject *)object,object->requested_animation,g_frame_actor_direction_variants_signed[object->direction]);
 frame_set_part_order((struct FrameObject *)object,0,4);
 frame_set_part_order((struct FrameObject *)object,1,2);
 frame_set_part_order((struct FrameObject *)object,2,3);
 object->before_step=resource_object_before_step;
 frame_set_variant_state((struct FrameObject *)object,0);
 return (struct FrameObject *)object;
}
asm(".align 2,0");
