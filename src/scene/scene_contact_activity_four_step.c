#include "scene_contact_activity_four_step.h"
#define STATE ((struct SceneContactActivityFourState *)g_scene_contact_state)

void scene_contact_activity_four_step(void)
{
    --g_scene_request.unknown_14;
    if (g_scene_request.unknown_14 == (unsigned int)-1) {
        scene_contact_activity_four_create_event();
        g_scene_request.unknown_14 =
            g_scene_contact_activity_four_rows[g_scene_contact_state->option].interval;
    }
    if ((unsigned char)scene_contact_activity_four_complete()) {
        audio_play_sequence_notification(27);
        scene_contact_add_activity_score(STATE->score);
        scene_contact_activity_four_clear_secondary();
        scene_contact_activity_four_reset_items();
    }
    if ((unsigned char)display_time_equal(&g_display_countdown,
                                          &g_scene_contact_activity_four_clock, 31)) {
        register const struct SceneContactActivityFourItem *items asm("r5");
        unsigned int i = 0;
        struct SceneContactState **state_slot;
        state_slot = &g_scene_contact_state;
        items = g_scene_contact_activity_four_items;
        for (; i <= 7; ++i) {
            struct SceneContactActivityFourState *state =
                (struct SceneContactActivityFourState *)*state_slot;
            register struct FrameObject *second asm("r3");
            unsigned int id;
            second = state->second[i];
            if (second) {
                register struct FrameObject *first asm("r1");
                unsigned short first_id;
                first = state->first[i];
                first_id = first->unknown_0a;
                if (first_id == second->unknown_0a) continue;
                id = first_id;
            } else {
                id = state->first[i]->unknown_0a;
            }
            state->score -= items[id].penalty;
        }
        if (((struct SceneContactActivityFourState *)*state_slot)->score <= 0)
            ((struct SceneContactActivityFourState *)*state_slot)->score = 1;
        scene_contact_add_activity_score(
            ((struct SceneContactActivityFourState *)*state_slot)->score);
        (*state_slot)->flags |= 2;
    }
}
