#include "scene_contact_activity_four.h"

#define STATE ((struct SceneContactActivityFourState *)g_scene_contact_state)

unsigned int scene_contact_activity_four_complete(void)
{
    unsigned int complete = 1;
    int i;
    struct SceneContactActivityFourState *state = STATE;

    if (((struct SceneContactCursor *)state->control)->state == 1) {
        for (i = 0; i <= 7; ++i) {
            if (!state->second[i] ||
                state->second[i]->unknown_0a != state->first[i]->unknown_0a) {
                complete = 0;
                break;
            }
        }
    } else {
        complete = 0;
    }
    return complete;
}

asm(".align 2,0");
