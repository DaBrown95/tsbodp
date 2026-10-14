#include "scene_contact_activity_four.h"

#define STATE ((struct SceneContactActivityFourState *)g_scene_contact_state)

void scene_contact_activity_four_reset_items(void)
{
    struct FramePoint position;
    int i;

    position.x = 212;
    position.y = 86;
    STATE->score = 0;
    for (i = 0; i <= 7; ++i) {
        unsigned int selected;
        struct FrameObject *object;
        struct SceneContactActivityFourState *state;

        if (STATE->first[i]) {
            frame_remove_object(STATE->first[i]);
            STATE->first[i] = 0;
        }
        selected = frame_random_range(1,
            g_scene_contact_activity_four_rows[g_scene_contact_state->option].count);
        STATE->selections[i] = selected;
        object = scene_contact_original_create_four_item(position, selected, i);
        state = STATE;
        state->first[i] = object;
        state->score +=
            g_scene_contact_activity_four_items[object->unknown_0a].penalty;
    }
}
