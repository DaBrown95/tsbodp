#include "scene_contact_activity_four.h"

#define STATE ((struct SceneContactActivityFourState *)g_scene_contact_state)

void scene_contact_activity_four_clear_secondary(void)
{
    int i;

    for (i = 0; i <= 7; ++i) {
        if (STATE->second[i]) {
            frame_remove_object(STATE->second[i]);
            STATE->second[i] = 0;
        }
    }
}
