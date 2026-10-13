#include "frame_render_effect.h"
#include "frame_transient_effect.h"
#include "display_time_hud.h"
void display_release_object_list(struct FrameObjectList *);

void frame_clear_scene_effects(void) {
    display_release_object_list(&g_frame_primary_list);
    frame_clear_transient_effects();
    frame_clear_render_effects();
    if (!g_display_countdown_scene->scene &&
        (g_display_countdown_scene->flags & 0x20)) {
        frame_release_transient_definition_tiles(0, 1);
        frame_release_transient_definition_tiles(0, 0);
    }
}
