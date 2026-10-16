#include "frame_actor_spawn_attachment.h"

void frame_tick_actor_spawn_attachment(struct FrameNeedEffectState *owner)
{
    struct FrameObject *actor;
    unsigned short *parameter = &owner->parameter;
    unsigned char count;
    if ((short)*parameter == 1) {
        count = frame_find_objects(7, 4, &actor, 1);
        if (count == 0) {
            frame_commit_need_effect(owner->object, 0);
            *parameter = count;
        }
    }
}
