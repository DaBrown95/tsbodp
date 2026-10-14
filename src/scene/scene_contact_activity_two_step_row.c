#include "scene_contact_activity_two.h"
void scene_contact_activity_two_step_row(struct FrameObject *base)
{
    struct SceneContactActivityTwoRowObject *object =
        (struct SceneContactActivityTwoRowObject *)base;
    unsigned char *phase = &object->phase;
    switch (*phase) {
    case 7:
        if (object->flags & 0x400000) {
            *phase = 11;
            object->timer = frame_random_range(30, 120);
            frame_set_animation_frame((struct FrameTickObject *)object, 0);
            object->flags &= ~0x400010u;
            if (frame_random_bounded(100) <= 9)
                audio_play_animation_cue(207);
        }
        break;
    case 11:
        if (--object->timer == 0xffffffffu) {
            frame_set_animation_record((struct FrameObject *)object,
                &g_scene_contact_activity_two_rows[object->subtype].animation);
            *phase = 7;
            object->flags |= 16;
        }
    case 12:
        if (object->flags & 0x400000) {
            frame_set_animation_record((struct FrameObject *)object,
                &g_scene_contact_activity_two_rows[object->subtype].animation);
            object->phase = 7;
        }
        break;
    }
}
asm(".align 2, 0");
