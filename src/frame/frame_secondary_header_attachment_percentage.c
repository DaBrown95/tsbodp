#include "frame_need_effect_secondary_header_jobs.h"

unsigned char frame_secondary_header_attachment_percentage(struct FrameNeedEffectState *owner)
{
    unsigned char result = 100;
    if ((short)owner->parameter == 2560)
        result = 25;
    return result;
}
/* Native two zero alignment bytes before the next entry. */
asm(".align 2,0");
