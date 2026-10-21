#include "scene_primary.h"

void scene_step_transient_and_views_unrooted_27df0(void)
{
    unsigned char index;
    frame_step_transient_effects();
    index = 0;
    if (index < g_scene_primary_views.count) {
        unsigned char *count = &g_scene_primary_views.count;
        do {
            scene_update_view(index);
            ++index;
        } while (index < *count);
    }
}
