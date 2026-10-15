#include "frame_need_effect_secondary_header_jobs.h"
unsigned int frame_initialize_secondary_header_jobs(struct FrameNeedEffectState *owner)
{
 if((short)owner->parameter==2560){
  ((struct FrameActorObject *)owner->object)->requested_animation=2;
  owner->optional=2;
 }
 ((struct FrameSecondaryHeaderOwnerWork *)owner)->active=0;
 return 1;
}
