#include "scene_map_selection.h"
#include "display_motion.h"
#include "save_stream.h"
#include "resource_conditions.h"
#include "frame_scene_motion.h"
#include "display_palette_lifecycle.h"

void scene_map_selection_initialize_objects(void)
{
    struct FrameObject *object = frame_create_scene_object(163, 303, 1, 1);
    g_display_scene_frame_objects[0] = object;
    g_scene_map_selection_origin_x = g_scene_map_selection_limits[g_scene_map_selection_mode].first;
    if (g_scene_map_selection_world_points[g_scene_map_selection_requested_world].x-g_scene_map_selection_origin_x>230)
        g_scene_map_selection_origin_x = g_scene_map_selection_limits[g_scene_map_selection_mode].last;
    ((struct FrameSceneMotionObject *)object)->state = 14;
    ((struct FrameSceneMotionObject *)g_display_scene_frame_objects[0])->variant = 11;
    frame_set_position(g_display_scene_frame_objects[0],
        (g_scene_map_selection_world_points[g_scene_map_selection_requested_world].x-g_scene_map_selection_origin_x)<<16,
        g_scene_map_selection_world_points[g_scene_map_selection_requested_world].y<<16);
    if (((const struct SceneMapSelectionWorldView *)&g_resource_game_state)->scene!=50
        && ((const struct SceneMapSelectionWorldView *)&g_resource_game_state)->flag!=1) {
        g_display_scene_frame_objects[1] = frame_create_scene_object(166, 304, 3, 1);
        ((struct FrameSceneMotionObject *)g_display_scene_frame_objects[1])->state = 14;
        ((struct FrameSceneMotionObject *)g_display_scene_frame_objects[1])->variant = 11;
        frame_set_position(g_display_scene_frame_objects[1],
            (g_scene_map_selection_world_points[((const struct SceneMapSelectionWorldView *)&g_resource_game_state)->scene].x-g_scene_map_selection_origin_x)<<16,
            g_scene_map_selection_world_points[((const struct SceneMapSelectionWorldView *)&g_resource_game_state)->scene].y<<16);
    }
    g_display_scene_frame_objects[2] = frame_create_scene_object(137, 277, 2, 1);
    g_display_scene_frame_objects[2]->flags &= ~1U;
}

asm(".align 2, 0");
