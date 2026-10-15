#include "scene_contact_activity_one.h"
#define STATE ((struct SceneContactActivityOneState*)g_scene_contact_state)
struct FrameObject *scene_contact_activity_one_create_primary(void) {
 struct FrameActorObject *object=(void*)frame_allocate_object(0);struct SceneContactActivityOneAppearance *appearance;
 object->direction=2;
 frame_set_position((struct FrameObject*)object,(unsigned int)g_scene_contact_activity_one_positions[STATE->option].x*65536u,(unsigned int)g_scene_contact_activity_one_positions[STATE->option].y*65536u);
 ((struct SceneContactActivityOneObject*)object)->contact_mode=0;((struct SceneContactActivityOneObject*)object)->double_size=0;((struct SceneContactActivityOneObject*)object)->layer=2;
 frame_enable_object_flags((struct FrameObject*)object,25);object->on_step=scene_contact_activity_one_step_primary;
 appearance=&g_scene_contact_activity_one_appearance;frame_load_actor_group_palette(appearance,0);frame_enable_parts((struct FrameObject*)object);
 frame_request_animation((struct FrameCommandObject*)object,0);
 frame_set_part_variants((struct FrameObject*)object,0,g_scene_contact_activity_one_part0_tables[appearance->group],0);
 frame_set_part_variants((struct FrameObject*)object,1,g_scene_contact_activity_one_part1_tables[appearance->group][appearance->variant],0);
 frame_set_animation_variant((struct FrameObject*)object,object->requested_animation,g_frame_actor_direction_variants_signed[object->direction]);
 frame_set_part_order((struct FrameObject*)object,0,4);frame_set_part_order((struct FrameObject*)object,1,5);
 object->before_step=resource_object_before_step;frame_set_variant_state((struct FrameObject*)object,0);return(struct FrameObject*)object;
}
asm(".align 2,0");
