#include "frame_need_effect_header_choices.h"
#include "display_need_effect_lifecycle.h"
struct FrameActorAttachmentRecord *frame_need_effect_nth_attachment(struct FrameNeedEffectState *owner,unsigned int ordinal)
{
    unsigned char count = 0, index = 0;
    for (; index < 3; index++)
        if (owner->records[index].actor)
            if (++count == ordinal)
                return &owner->records[index];
    return 0;
}
