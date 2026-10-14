#include "scene_contact_activity_seven.h"
struct FrameObject *scene_contact_activity_seven_create_primary(void) {
 struct FrameActorObject *object=(void *)frame_allocate_object(0);
 struct SceneContactActivitySevenAppearance *appearance;
 frame_set_position((struct FrameObject *)object,120*65536,104*65536);
 object->direction=4;FLAGS(object)->contact_mode=0;FLAGS(object)->double_size=0;FLAGS(object)->layer=2;
 frame_enable_object_flags((struct FrameObject *)object,25);
 object->on_step=scene_contact_activity_seven_step_primary;
 appearance=&g_scene_contact_activity_seven_appearance;
 frame_load_actor_group_palette(appearance,0);
 frame_enable_parts((struct FrameObject *)object);
 frame_request_animation((struct FrameCommandObject *)object,0);
 frame_set_part_variants((struct FrameObject *)object,0,g_scene_contact_activity_seven_part0[appearance->group],0);
 frame_set_part_variants((struct FrameObject *)object,1,g_scene_contact_activity_seven_part1[appearance->group][appearance->variant],0);
 frame_set_part_variants((struct FrameObject *)object,2,g_scene_contact_activity_seven_part2[appearance->group][STATE->option],1);
 frame_define_palette_slot(1,g_scene_contact_activity_seven_palette1);
 frame_set_animation_variant((struct FrameObject *)object,object->requested_animation,g_frame_actor_direction_variants_signed[object->direction]);
 frame_set_part_order((struct FrameObject *)object,0,4);
 frame_set_part_order((struct FrameObject *)object,1,5);
 frame_set_part_order((struct FrameObject *)object,2,6);
 object->before_step=resource_object_before_step;
 frame_set_variant_state((struct FrameObject *)object,0);
 return (struct FrameObject *)object;
}
