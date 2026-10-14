#include "scene_contact_activity_four_primary.h"

#define STATE ((struct SceneContactActivityFourEventState *)g_scene_contact_state)

void scene_contact_activity_four_step_primary_object(struct FrameObject *object)
{
    if (!(g_scene_contact_state->flags & 2)) {
        if (g_input_current[0] & 16) {
            object->next_position.x =
                (int)((unsigned int)object->position.x + 0x30000);
            if (object->next_position.x <= 0xa9ffff)
                object->position.x = object->next_position.x;
        } else if (g_input_current[0] & 32) {
            object->next_position.x =
                (int)((unsigned int)object->position.x - 0x30000);
            if (object->next_position.x > 0xe0000)
                object->position.x = object->next_position.x;
        }
        if (((struct SceneContactCursor *)STATE->control)->state == 1) {
            STATE->control->position.x = object->position.x;
            if (g_input_pressed[0] & 1) {
                audio_play_animation_cue(185);
                {
                    register struct SceneContactActivityFourPrimaryState
                        *state asm("r2");

                    object->flags |= 16;
                    state = (struct SceneContactActivityFourPrimaryState *)
                        g_scene_contact_state;
                    {
                        struct FrameObject *control;
                        unsigned int flags;

                        control = (struct FrameObject *)state->control.address;
                        flags = control->flags;
                        control->flags = flags | 16;
                    }
                    ((struct SceneContactCursor *)
                        (struct FrameObject *)state->control.address)->state = 3;
                    state = (struct SceneContactActivityFourPrimaryState *)
                        g_scene_contact_state;
                    ((struct FrameObject *)state->control.address)->velocity.y =
                        -0xc0000;
                    ((struct FrameObject *)state->control.address)->acceleration.y =
                        0x8000;
                }
            }
        }
    }
    if (object->flags & 0x400000) {
        object->flags &= ~(0x400000 | 16);
        frame_set_animation_frame((struct FrameTickObject *)object, 0);
    }
}

asm(".align 2,0");
