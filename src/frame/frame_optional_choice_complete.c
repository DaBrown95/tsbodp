#include "frame_optional_choice_apply.h"
#include "frame_actor_finish.h"

struct FrameObject *frame_optional_choice_complete(unsigned int kind)
{
    struct FrameObject *result = 0;
    int x, y;

    if (frame_find_scene_target(&x, &y) == 1)
        result = frame_create_actor(kind, 0, x, y);
    return result;
}
