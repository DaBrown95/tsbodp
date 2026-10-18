#include "frame.h"
#include "frame_actor_state.h"

int frame_object_near_view_11b8(struct FrameObject *object, FrameU8 view)
{
    struct FramePoint origin, point;

    if (object->forced_visible == 1)
        return 1;
    frame_get_view_origin(&origin, view);
    frame_point_to_integer(&object->position, &point);
    {
        register int margin asm("r6") = 100;
        register int view_x asm("r4") = origin.x;

        if (point.x >= view_x - 100
                && point.y >= origin.y - 100
                && point.x <= ({ register int upper asm("r0") = margin + 240; view_x + upper; })
                && point.y <= ({ register int upper asm("r0") = margin + 160; origin.y + upper; }))
            return 1;
    }
    return 0;
}
