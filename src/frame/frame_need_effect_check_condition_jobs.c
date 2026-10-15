#include "frame_need_effect_condition_jobs.h"
#include "frame_need_effect_optional_jobs.h"
#include "resource_conditions.h"
#include "frame_actor_social.h"

unsigned int frame_need_effect_check_condition_jobs(struct FrameNeedEffectState *owner,struct FrameObject *actor)
{
 if ((unsigned char)frame_need_effect_optional_one_ready(owner) ||
     (unsigned char)condition_is_active(1,3,2))
  return 1;
 return 0;
}
asm(".align 2, 0");
