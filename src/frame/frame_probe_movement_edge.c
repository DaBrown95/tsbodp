#include "frame_movement.h"

static inline struct FramePoint edge_endpoint(const struct FramePoint *point)
{
    struct FramePoint copy;
    copy = *point;
    return copy;
}

unsigned int frame_probe_movement_edge(unsigned int direction, const int *bounds)
{
    struct FramePoint endpoint;
    int length, step;
    struct FramePoint position;
    struct FramePoint delta;
    unsigned int contact = 0;

    switch (direction) {
    case 0: {
        int initial_x = bounds[0];
        int initial_y;
        position.x = initial_x;
        initial_y = bounds[2];
        position.y = initial_y;
        endpoint.x = bounds[1];
        endpoint.y = position.y;
        delta.x = 1;
        delta.y = 0;
        length = endpoint.x - initial_x;
        break;
    }
    case 2: {
        int initial_x = bounds[1];
        int initial_y;
        position.x = initial_x;
        initial_y = bounds[2];
        position.y = initial_y;
        endpoint.x = position.x;
        endpoint.y = bounds[3];
        delta.x = 0;
        delta.y = 1;
        length = endpoint.y - initial_y;
        break;
    }
    case 4: {
        int initial_x = bounds[1];
        int initial_y;
        position.x = initial_x;
        initial_y = bounds[3];
        position.y = initial_y;
        endpoint.x = bounds[0];
        endpoint.y = position.y;
        delta.x = -1;
        delta.y = 0;
        length = initial_x - endpoint.x;
        break;
    }
    case 6: {
        int initial_x = bounds[0];
        int initial_y;
        position.x = initial_x;
        initial_y = bounds[3];
        position.y = initial_y;
        endpoint.x = position.x;
        endpoint.y = bounds[2];
        delta.x = 0;
        delta.y = -1;
        length = initial_y - endpoint.y;
        break;
    }
    default:
        length = 0;
        break;
    }

    if (g_frame_movement_filter[0] == 255) {
        g_frame_movement_filter[0] = frame_map_terrain_at(edge_endpoint(&endpoint));
        g_frame_movement_filter[1] = frame_map_terrain_at(position);
    }
    for (step = 0; step < length;
         position.x += delta.x * 8, position.y += delta.y * 8, step += 8) {
        unsigned int value = frame_map_terrain_at(position);
        if (value) {
            contact = value;
            if (frame_movement_is_contact(value))
                break;
        }
    }
    if (!frame_movement_is_contact(contact)) {
        unsigned int value = frame_map_terrain_at(edge_endpoint(&endpoint));
        if (value)
            contact = value;
    }
    return contact;
}
asm(".align 2, 0");
