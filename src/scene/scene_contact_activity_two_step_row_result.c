#include "scene_contact_activity_two.h"
#define STATE ((struct SceneContactActivityTwoState *)g_scene_contact_state)
void scene_contact_activity_two_step_row_result(struct FrameObject *object) {
 if (STATE->entries[STATE->selected_row].object->shared_slot == 3) {
  object->flags |= 3;
  scene_contact_activity_two_reset_controls();
  scene_contact_activity_two_draw_row(STATE->selected_row);
  audio_play_animation_cue(199);
 }
}
asm(".align 2, 0");
