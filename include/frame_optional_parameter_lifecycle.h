#ifndef FRAME_OPTIONAL_PARAMETER_LIFECYCLE_H
#define FRAME_OPTIONAL_PARAMETER_LIFECYCLE_H

#include "frame_need_effect_optional_completion.h"

/* Observed row-138 initializer and F8 tick. The initializer's unused formal
 * and historical result declaration are not uniquely established; its caller
 * ignores that result. These declarations retain the actual owner contract. */
unsigned int frame_initialize_optional_parameter_attachment_job(
    struct FrameNeedEffectState *);
void frame_tick_optional_parameter_attachment_job(struct FrameNeedEffectState *);

#endif
