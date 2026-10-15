#include "frame_need_effect_condition_jobs.h"
#include "frame_need_effect_optional_jobs.h"
#include "resource_conditions.h"
#include "frame_actor_social.h"
unsigned int frame_need_effect_select_condition_jobs(struct FrameNeedEffectState *owner,unsigned char *choices)
{
 unsigned int count=1;
 choices[0]=7;
 if ((unsigned char)frame_need_effect_optional_one_ready(owner) &&
     (unsigned char)condition_is_active(1,3,2)) {
  count=2;
  choices[1]=45;
 }
 if ((unsigned char)condition_is_active(1,4,1))
  choices[count]=44;
 return 1;
}
