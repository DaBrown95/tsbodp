#include "frame.h"
#include "input.h"
int frame_check_visibility(struct FrameObject *object)
{
    struct FramePoint origin, point;
    FrameU32 count;
    FrameU8 i;
    int visible = 0;
    object->flags &= ~0x40001000;
    if (object->forced_visible == 1) {
        object->flags |= 0x1000;
        object->flags |= 0x40000000;
    }
    if (object->flags & 0x200000) {
        object->flags |= 0x40001000;
        return 1;
    }
    count = g_input_config.player_count ? g_input_config.player_count : 1;
    for (i = 0; i < count; i++) {
        int right, left;
        frame_get_view_origin(&origin, i);
        frame_project_point(&object->position, &point);
        if (object->render_special < 0) {
            right = point.x - object->bound_x0;
            left = point.x - object->bound_x1;
        } else {
            right = point.x + object->bound_x1;
            left = point.x + object->bound_x0;
        }
        if (right >= origin.x && left <= origin.x + 240
                && point.y + object->bound_y1 >= origin.y
                && point.y + object->bound_y0 <= origin.y + 160) {
            object->flags |= 0x1000;
            if (i == g_input_config.local_player)
                object->flags |= 0x40000000;
            visible = 1;
        }
    }
    return visible;
}
