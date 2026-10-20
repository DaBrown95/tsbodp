#include "frame_actor_needs.h"
#include "input.h"
#include "view_math.h"

/* Independently bounded entry; incoming roots and unused formals are unknown. */
void frame_unrooted_input_velocity_7ec8(struct FrameObject *object,
                                      struct FramePoint *velocity)
{
    if (g_input_current[g_frame_actor_need_input.local_player] & 2) {
        frame_make_velocity(velocity, object->flags,
                            ((struct FrameActorObject *)object)->direction,
                            (int)(unsigned int)
                                (((struct FrameActorObject *)object)->speed * 1.1));
        frame_request_animation((struct FrameCommandObject *)object, 55);
    } else {
        frame_make_velocity(velocity, object->flags,
                            ((struct FrameActorObject *)object)->direction,
                            (int)(unsigned int)
                                (((struct FrameActorObject *)object)->speed * 0.6));
        frame_request_animation((struct FrameCommandObject *)object, 55);
    }
}
