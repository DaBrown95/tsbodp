#include "scene_contact_activity_two_access.h"
#define STATE ((struct SceneContactActivityTwoState *)g_scene_contact_state)
void scene_contact_activity_two_reset_controls(void) {
 struct SceneContactActivityTwoControlWord flags;
 flags = scene_contact_activity_two_read_control(STATE->primary);
 flags.bits |= 17;
 scene_contact_activity_two_write_control(STATE->primary,flags);
 frame_set_animation_program(STATE->primary,(struct FrameSpriteResource *)&g_scene_contact_activity_two_primary_animation,g_scene_contact_activity_two_primary_program,0);
 flags = scene_contact_activity_two_read_control(STATE->secondary);
 flags.bits &= ~1u;
 scene_contact_activity_two_write_control(STATE->secondary,flags);
 frame_set_animation_program(STATE->secondary,(struct FrameSpriteResource *)&g_scene_contact_activity_two_secondary_animation,g_scene_contact_activity_two_secondary_program,0);
 STATE->flags &= ~2u;
 STATE->event_hits = 0;
}
asm(".align 2, 0");
