#include "frame_actor_palette_menu.h"
#include "scene_request.h"
void frame_step_palette_menu_choices(void)
{
 struct SceneRequest *state = &g_scene_request;
 /* The scene word is reused as the selected row in this menu. */
 unsigned int previous = state->scene;
 unsigned int *row = &state->scene;
 unsigned int *choices;
 input_step_local_vertical_pressed(row, 0, 7, 1, 0);
 if (!g_frame_actor_palette_menu_enabled[state->scene]) {
  unsigned int *skip_row = row;
  const unsigned char *enabled = g_frame_actor_palette_menu_enabled;
  do {
   input_step_local_vertical_pressed(skip_row, 0, 7, 1, 0);
  } while (!*(const unsigned char *)(state->scene + (unsigned int)enabled));
 }
 {
 struct SceneRequest *state2 = &g_scene_request;
 if (previous != state2->scene)
  audio_play_animation_cue(0);
 choices = g_frame_actor_palette_menu_choices;
 previous = choices[state2->scene];
 input_step_local_horizontal_pressed(&choices[state2->scene], 0, g_frame_actor_palette_menu_counts[state2->scene] - 1, 1, 0);
 if (previous != choices[state2->scene]) {
  if (state2->scene == 0)
   frame_draw_palette_menu_row(5);
  audio_play_animation_cue(0);
 }
 }
 frame_update_palette_menu_actor();
}
asm(".align 2, 0");
