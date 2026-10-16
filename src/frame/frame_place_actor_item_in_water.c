#include "frame_actor_items.h"

void frame_place_actor_item_in_water(struct FrameObject *object, unsigned char *used)
{
    int index;
    struct FramePoint point;

    do {
        index = frame_random_range(0, 42);
    } while (frame_map_terrain_at(g_frame_actor_item_water_points[index]) != 1);
    point = g_frame_actor_item_water_points[index];
    used[index] = 1;
    frame_set_position(object, (unsigned int)point.x * 65536u,
                       (unsigned int)point.y * 65536u);
}
asm(".align 2,0");
