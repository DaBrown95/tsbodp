#include "scene_contact_activity_two_access.h"
#define STATE ((struct SceneContactActivityTwoState *)g_scene_contact_state)
void scene_contact_activity_two_begin_transfer(unsigned int first,unsigned char second) {
 struct SceneContactActivityTwoControlWord flags;
 flags = scene_contact_activity_two_read_control(STATE->event);
 flags.bits |= 16;
 scene_contact_activity_two_write_control(STATE->event,flags);
 frame_set_position(STATE->event,0,88*65536);
 STATE->event->on_step = scene_contact_activity_two_step_event;
 STATE->sound_handle = audio_play_animation_cue(203);
 ((struct FrameActorObject *)STATE->event)->direction = second + 1;
 ((struct FrameActorObject *)STATE->event)->speed = (int)((first + 17u) << 16) / 4;
 STATE->event = scene_contact_activity_two_create_event(frame_random_range(0,2));
}
asm(".align 2, 0");
