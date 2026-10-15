#ifndef FRAME_POSITION_CYCLE_JOBS_H
#define FRAME_POSITION_CYCLE_JOBS_H
#include "frame_need_effect_optional_jobs.h"
unsigned int frame_position_cycle_step(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
unsigned int frame_position_cycle_choices(struct FrameNeedEffectState *,unsigned char *);
unsigned int frame_position_cycle_begin(struct FrameNeedEffectState *,struct FrameObject *,unsigned int);
unsigned int frame_position_cycle_dispatch(struct FrameNeedEffectState *,struct FrameObject *);
#endif
