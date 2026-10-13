#include "frame.h"
void frame_update_bounds(struct FrameObject *object)
{
    struct FramePoint position;
    union { FrameU32 value; FrameU16 words[2]; } key;
    if (object->flags & 0x10000000) {
        position.x = (short)(object->position.x >> 16);
        position.y = (short)(object->position.y >> 16);
        frame_locate_bounds(g_frame_registration, &position, &key);
        if (key.words[0] != *(FrameU16 *)object->registered_bounds) {
            frame_grid_remove_occupancy(g_frame_registration, object->registered_bounds, 16);
            frame_grid_add_occupancy(g_frame_registration, &key, 16);
            *(FrameU32 *)object->registered_bounds = key.value;
        }
    }
}
