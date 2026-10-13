#include "frame_actor_palette_menu.h"
void frame_create_palette_menu_actors(void)
{
 const char *text;
 struct FrameActorObject *object = (struct FrameActorObject *)frame_allocate_object(0);
 struct FrameObject **objects = g_frame_actor_palette_menu_objects;
 const unsigned char *definition;
 objects[0] = (struct FrameObject *)object;
 frame_set_position((struct FrameObject *)object,
   (unsigned int)(int)g_frame_actor_palette_menu_position.x << 16,
   (unsigned int)(int)g_frame_actor_palette_menu_position.y << 16);
 object->direction = 4;
 object->oam.palette = 1;
 object->flags = 17;
 definition = g_frame_actor_palette_pair_definition;
 frame_load_actor_group_palette(definition, 1);
 frame_load_actor_group_alternate_palette(definition, 2);
 frame_enable_parts((struct FrameObject *)object);
 frame_request_animation((struct FrameCommandObject *)object, 0);
 frame_set_part_variants((struct FrameObject *)object, 0, g_frame_actor_palette_scene_part0[definition[0]], 1);
 frame_set_part_variants((struct FrameObject *)object, 1, g_frame_actor_palette_scene_part1[definition[0]][definition[2]], 2);
 frame_set_animation_variant((struct FrameObject *)object, object->requested_animation,
   g_frame_actor_direction_variants_signed[object->direction]);
 frame_set_part_order((struct FrameObject *)object, 0, 4);
 objects[1] = frame_create_scene_object(10, 0, 3, 1);
 objects[2] = frame_create_scene_object(0, 4, 10, 1);
 objects[3] = frame_create_scene_object(16, 7, 4, 1);
 objects[6] = frame_create_scene_object(11, 1, 7, 0);
 objects[4] = frame_create_scene_object(23, 7, 5, 1);
 objects[5] = frame_create_scene_object(21, 6, 9, 1);
 objects[8] = frame_create_scene_object(8, 234, 8, 1);
 objects[9] = frame_create_scene_object(31, 235, 8, 1);
 display_load_palette_alternate(g_frame_actor_palette_menu_extra_palette, 96, 16);
 display_text_copy_field_zero((const char *)((unsigned int)definition - 16));
 display_text_select_font(1, 0, 0);
 text = display_scene_lookup_text(0x184f);
 objects[7] = display_scene_create_label(9, &text);
 transition_object_set_state(objects[7], 14);
 display_text_set_background_control(g_frame_actor_palette_menu_background);
}
asm(".align 2, 0");
