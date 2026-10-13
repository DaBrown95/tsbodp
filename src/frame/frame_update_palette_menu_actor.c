#include "frame_actor_palette_menu.h"
void frame_update_palette_menu_actor(void)
{
 struct FrameActorPaletteMenuState *state = &g_frame_actor_palette_menu_state;
 unsigned char *definition = state->selectors;
 unsigned char current = definition[0];
 unsigned int *choices = g_frame_actor_palette_menu_choices;
 unsigned char *variant;
 struct FrameObject **objects;
 if (current != choices[0]) {
  display_text_select_font(1, 0, 0);
  display_text_set_object_string(g_frame_actor_palette_menu_objects[7], (const char *)state + 16);
  display_text_set_background_control(g_frame_actor_palette_menu_background);
 }
 state->selectors[0] = choices[0];
 state->selectors[1] = choices[1];
 {
  unsigned int value = choices[2];
  variant = definition + 2;
  *variant = value;
 }
 state->selectors[3] = choices[3];
 state->selectors[4] = choices[4];
 state->selectors[5] = choices[5];
 state->selectors[6] = choices[6];
 frame_load_actor_group_palette(definition, 1);
 frame_load_actor_group_alternate_palette(definition, 2);
 objects = g_frame_actor_palette_menu_objects;
 frame_set_part_variants(objects[0], 0, g_frame_actor_palette_scene_part0[definition[0]], 1);
 frame_set_part_variants(objects[0], 1, g_frame_actor_palette_scene_part1[definition[0]][*variant], 2);
 frame_set_animation_variant(objects[0], ((struct FrameActorGroupAnimationView *)objects[0])->animation, g_frame_actor_direction_variants_signed[((struct FrameActorObject *)objects[0])->direction]);
}
asm(".align 2, 0");
