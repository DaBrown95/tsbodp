#include "save_world_display.h"
#include "frame_scene_player.h"

void save_world_create_row_indicator(struct SaveWorldTransitionRow *row,
                                     unsigned char index)
{
    struct FrameObject *object = frame_allocate_object(24);
    row->objects[index] = object;
    object->unknown_0a = 0;
    object->flags = 0x200019;
    object->display_layer = 0;
    frame_set_position(object,
        ((g_save_world_indicator_coordinates[index].x << 3) + 2) << 16,
        (g_save_world_indicator_coordinates[index].y << 19) - 0x20000);
    frame_acquire_palette_slot(object, 6);
    frame_set_animation_record(object, &g_save_world_indicator_animation);
}
