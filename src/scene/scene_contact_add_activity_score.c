#include "scene_contact_activity_four.h"

void scene_contact_add_activity_score(int delta)
{
    g_scene_contact_state->amount =
        (unsigned short)g_scene_contact_state->amount + (unsigned int)delta;
    g_scene_contact_state->flags |= 8;
    if (delta > 0)
        g_scene_contact_state->result = 1;
    else if (delta < 0)
        g_scene_contact_state->result = 2;
}
