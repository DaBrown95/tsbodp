#include "scene_map_selection.h"
#include "display_motion.h"
#include "save_stream.h"
#include "resource_conditions.h"
#include "frame_scene_motion.h"
#include "display_palette_lifecycle.h"

unsigned int scene_map_selection_entry_under_cursor(void)
{
    unsigned char index = 0;
    struct FrameObject *object = g_display_scene_frame_objects[0];
    const struct DisplayBackgroundSystem *system = &g_display_background_system;
    int x = object->position.x+system->backgrounds[0].position_x;
    const struct SceneMapSelectionPoint *points = g_scene_map_selection_points.rows;
    const unsigned int *point_y = &g_scene_map_selection_points.words[1];
    const struct SceneMapSelectionBounds *bounds = g_scene_map_selection_bounds;
    do {
        if (x>(int)((points[index].x-bounds[index].left)<<16)
            && x<(int)((points[index].x+bounds[index].right)<<16)) {
            int y = object->position.y+system->backgrounds[0].position_y;
            if (y>(int)((point_y[index*2]-bounds[index].top)<<16)
                && y<(int)((point_y[index*2]+bounds[index].bottom)<<16))
                return index;
        }
        ++index;
    } while (index<=25);
    return 255;
}

asm(".align 2, 0");
