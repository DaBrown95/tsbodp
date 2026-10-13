#include "frame_actor_palette_scene.h"
void frame_create_palette_scene_actor(unsigned int position)
{
 struct FrameActorObject *object;
 const unsigned char *definition;
 const unsigned char *kinds = g_frame_actor_palette_scene_resource;
 struct FrameActorPaletteSceneSelection *selection = &g_frame_actor_palette_scene_selection;
 kinds += 4;
 if (kinds[selection->index] == 1) {
  object = (struct FrameActorObject *)frame_allocate_object(0);
  g_frame_actor_palette_scene_object = (struct FrameObject *)object;
  frame_set_position((struct FrameObject *)object,
    (unsigned int)(int)g_frame_actor_palette_scene_positions[position].x << 16,
    (unsigned int)(int)g_frame_actor_palette_scene_positions[position].y << 16);
  object->flags = 25;
  object->direction = 4;
  object->oam.palette = 2;
  definition = g_frame_actor_palette_scene_rows[selection->index].selectors;
  frame_load_actor_group_palette(definition, 2);
  frame_load_actor_group_alternate_palette(definition, 3);
  frame_enable_parts((struct FrameObject *)object);
  frame_request_animation((struct FrameCommandObject *)object, 0);
  frame_set_part_variants((struct FrameObject *)object, 0, g_frame_actor_palette_scene_part0[definition[0]], 2);
  frame_set_part_variants((struct FrameObject *)object, 1, g_frame_actor_palette_scene_part1[definition[0]][definition[2]], 3);
  frame_set_animation_variant((struct FrameObject *)object, object->requested_animation,
    g_frame_actor_direction_variants_signed[object->direction]);
  frame_set_part_order((struct FrameObject *)object, 0, 4);
 }
}
asm(".align 2, 0");
