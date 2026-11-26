#include "frame_optional_attachment_dispatch.h"
#include "frame_optional_routes_12_23_60.h"

unsigned int frame_dispatch_optional_attachment_kinds_12_28_45(struct FrameNeedEffectState *owner,
                                                      struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(owner, actor);
    unsigned int result;
    switch (job->kind) {
        case 28:
        case 30:
        case 31:
        case 32:
        case 33:
            result = frame_step_optional_attachment_kinds_28_30_to_33(owner, job);
            break;
        case 12:
            result = frame_step_optional_attachment_kind_12_keep_direction(owner, job);
            break;
        case 45:
            result = frame_step_optional_attachment_kind_45_actor_effect_anim_45(owner, job);
            break;
        default:
            result = 0;
            break;
    }
    return result;
}
asm(".align 2, 0");
