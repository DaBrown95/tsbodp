#ifndef FRAME_SHARED_OPTIONAL_JOBS_H
#define FRAME_SHARED_OPTIONAL_JOBS_H
#include "frame_need_effect_optional_jobs.h"
unsigned int frame_shared_optional_choices(struct FrameNeedEffectState *,unsigned char *);
unsigned int frame_shared_optional_begin(struct FrameNeedEffectState *,struct FrameObject *,unsigned int);
unsigned int frame_shared_optional_dispatch(struct FrameNeedEffectState *,struct FrameObject *);
unsigned int frame_shared_optional_indicator_step(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
unsigned int frame_shared_optional_timed_step(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
#endif
