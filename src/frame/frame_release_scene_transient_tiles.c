#include "frame_render_effect.h"
#include "frame_transient_effect.h"
extern unsigned int g_scene_id;

void frame_release_scene_transient_tiles(void) {
    if (g_scene_id <= 14)
        frame_release_transient_definition_tiles(0, 2);
    frame_release_transient_definition_tiles(0, 3);
    frame_release_transient_definition_tiles(0, 6);
    frame_release_transient_definition_tiles(0, 7);
}
