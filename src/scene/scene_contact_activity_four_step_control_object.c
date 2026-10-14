#include "scene_contact_activity_four_objects.h"

#define STATE ((struct SceneContactActivityFourEventState *)g_scene_contact_state)
void scene_contact_activity_four_step_control_object(struct FrameObject *object)
{
    struct SceneContactActivityFourControlObject *cursor =
        (struct SceneContactActivityFourControlObject *)object;

    switch (cursor->state) {
    case 1:
        break;
    case 2:
        if (object->flags & 0x400000) {
            cursor->timer = 10;
            cursor->state = 7;
            object->flags &= ~(0x400000 | 17);
            object->position.x = STATE->object->position.x;
        }
        break;
    case 3:
        object->next_position.y = (int)((unsigned int)object->next_position.y +
            (unsigned int)object->velocity.y);
        object->velocity.y = (int)((unsigned int)object->velocity.y +
            (unsigned int)object->acceleration.y);
        if (object->velocity.y > 0)
            object->unknown_0a = 1;
        if (object->next_position.y > 0x8bffff) {
            int lower, upper;

            object->velocity.y = 0;
            object->acceleration.y = 0;
            object->position.y = 0x8c0000;
            object->unknown_0a = 0;
            lower = (int)((unsigned int)STATE->object->position.x - 0xe0000);
            upper = (int)((unsigned int)STATE->object->position.x + 0xe0000);
            if (object->position.x < lower || object->position.x > upper) {
                int i;

                audio_play_animation_cue(187);
                for (i = 0; i <= 7; i++) {
                    if (STATE->second[i]) {
                        frame_remove_object(STATE->second[i]);
                        STATE->second[i] = 0;
                    }
                }
                cursor->state = 2;
                frame_set_animation_record(object,
                    &g_scene_contact_activity_four_control_failed_animation);
                g_scene_contact_state->flags |= 2;
            } else {
                audio_play_animation_cue(186);
                cursor->state = 1;
                object->flags &= ~16;
                frame_set_animation_frame((struct FrameTickObject *)object, 0);
            }
        } else {
            object->position.y = object->next_position.y;
        }
        break;
    case 7:
        if ((cursor->timer = (int)((unsigned int)cursor->timer - 1)) == -1) {
            cursor->state = 1;
            object->flags |= 1;
            frame_set_animation_record(object,
                &g_scene_contact_activity_four_control_animation);
            g_scene_contact_state->flags &= ~2;
        }
        break;
    }
}

asm(".align 2,0");
