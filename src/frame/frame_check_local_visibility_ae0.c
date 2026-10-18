#include "frame.h"
#include "frame_actor_state.h"
#include "input.h"

int frame_check_local_visibility_ae0(struct FrameObject *object)
{
    struct FramePoint origin, point;

    if (object->forced_visible == 1)
        return 1;
    frame_get_view_origin(&origin, g_input_config.local_player);
    frame_point_to_integer(&object->position, &point);
    if (point.x + object->bound_x1 >= origin.x
            && point.x + object->bound_x0 <= origin.x + 240
            && point.y + object->bound_y1 >= origin.y
            && point.y + object->bound_y0 <= origin.y + 160) {
        object->flags |= 0x40000000;
        return 1;
    }
    return 0;
}
asm(".align 2,0");
