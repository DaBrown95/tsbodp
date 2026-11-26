#include "revision.h"
#include "scene_link_catalog.h"
#define STATE (((struct SceneLinkCatalogActor *)actor)->state)
unsigned int scene_link_catalog_try_entry(struct FrameObject *actor, unsigned int entry)
{
    unsigned int ok;
#if TSBO_REVISION
    if (entry == 141) {
        if (g_scene_id == 9 && STATE == 16)
            ok = 1;
        else {
            scene_link_catalog_draw_panel(1);
            ok = 0;
        }
    } else
#else
    if (entry == 141 && g_scene_id == 9 && STATE == 16)
        ok = 1;
    else
#endif
        if (entry == 255 || !frame_world_in_idle_exclusion_set(g_scene_id) || STATE != 16) {
        scene_link_catalog_draw_panel(1);
        ok = 0;
    } else if (entry <= 117 || entry == 125
#if !TSBO_REVISION
               || entry == 141
#endif
    ) {
        if (g_scene_link_catalog_world.collection->groups[g_scene_id].count > 24) {
            scene_link_catalog_draw_panel(4);
            ok = 0;
        } else
            ok = 1;
    } else if (entry == 139 || entry - 195 <= 5)
        ok = 1;
    else {
        scene_link_catalog_draw_panel(3);
        ok = 0;
    }
    if (ok != 1)
        return 0;
    transition_object_set_state(actor, 22);
    frame_set_variant_state(actor, 0);
    ((struct SceneLinkCatalogActor *)actor)->selected = 1;
    ((struct SceneLinkCatalogActor *)actor)->selected_index = g_scene_request.scene - 5;
    audio_play_animation_cue(7);
    resource_submit_scene(1, 2, g_scene_id);
    return 1;
}
asm(".align 2, 0");
