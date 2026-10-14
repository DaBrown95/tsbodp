#include "frame_optional_three_effect.h"

unsigned int frame_optional_three_effect_initialize(struct FrameNeedEffectState *base) {
 ((struct FrameOptionalThreeEffectState *)base)->active=0;
 return 1;
}
asm(".align 2, 0");
