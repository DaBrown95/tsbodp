#include "scene_contact_activity_four_event.h"

#define STATE ((struct SceneContactActivityFourEventState *)g_scene_contact_state)

void scene_contact_activity_four_step_event(struct FrameObject *object)
{
    struct SceneContactActivityFourEventState *state;
    struct FrameObject *control;
    struct FramePoint lower, upper;

    object->next_position.word.x = (int)((unsigned int)object->position.x +
        (unsigned int)object->velocity.x);
    object->next_position.word.y = (int)((unsigned int)object->position.y +
        (unsigned int)object->velocity.y);
    state = STATE;
    control = state->control;
    lower.x = (int)((unsigned int)control->position.x - 0xc0000);
    lower.y = (int)((unsigned int)control->position.y - 0xa0000);
    upper.x = (int)((unsigned int)control->position.x + 0xc0000);
    upper.y = (int)((unsigned int)control->position.y + 0xa0000);
    if (control->unknown_0a == 0 &&
        object->next_position.word.x > lower.x && object->next_position.word.x < upper.x &&
        object->next_position.word.y > lower.y && object->next_position.word.y < upper.y) {
        object->flags |= 2;
        if (!state->second[state->current]) {
            struct FramePoint point;

            point.x = 212;
            point.y = 30;
            {
                struct FrameObject *created =
                    scene_contact_activity_four_create_item(point,
                        object->unknown_0a, state->current);

                STATE->second[STATE->current] = created;
            }
        } else {
            frame_set_animation_frame(
                (struct FrameTickObject *)state->second[state->current],
                (unsigned char)object->unknown_0a);
            STATE->second[STATE->current]->unknown_0a = object->unknown_0a;
        }
        STATE->control->unknown_0a = 1;
        if (object->unknown_0a == 0) {
            --STATE->score;
            if (STATE->score <= 0)
                STATE->score = 1;
            audio_play_animation_cue(189);
        } else {
            audio_play_animation_cue(188);
        }
    } else {
        if ((object->unknown_12[0] == 2 &&
             object->next_position.word.x > 0xb7ffff) ||
            (object->unknown_12[0] == 6 && object->next_position.word.x <= 0))
            object->flags |= 2;
        else {
            object->position.x = object->next_position.word.x;
            object->position.y = object->next_position.word.y;
        }
    }
}

asm(".align 2,0");
