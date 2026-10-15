#include "frame_need_effect_header_choices.h"
#include "display_need_effect_lifecycle.h"
unsigned int frame_need_effect_select_header_choices(struct FrameNeedEffectState *owner,unsigned char *choices)
{
    unsigned char index = 0;
    if (frame_need_effect_attachment_count(owner) == 1 &&
        frame_need_effect_nth_attachment((struct FrameActorAttachmentOwner *)owner,1)->kind == 50)
        choices[index++] = 0;
    else if (frame_need_effect_attachment_count(owner) == 1 || owner->kind == 75)
        choices[index++] = 49;
    else if (frame_need_effect_attachment_count(owner) == 0) {
        choices[index++] = 49;
        choices[index++] = 50;
    }
    return 1;
}
asm(".align 2, 0");
