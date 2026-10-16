#ifndef FRAME_ACTOR_ATTACHMENT_JOBS_12_31_33_45_H
#define FRAME_ACTOR_ATTACHMENT_JOBS_12_31_33_45_H

#include "frame_need_effect_optional_completion.h"
#include "resource_conditions.h"
#include "frame_actor_social.h"

unsigned int frame_step_attachment_jobs_31_33(struct FrameNeedEffectState *,
                                              struct FrameActorAttachmentRecord *);
unsigned int frame_step_attachment_job_12_358b0(struct FrameNeedEffectState *,
                                               struct FrameActorAttachmentRecord *);
unsigned int frame_step_attachment_job_45_3594c(struct FrameNeedEffectState *,
                                               struct FrameActorAttachmentRecord *);
unsigned int frame_dispatch_attachment_jobs_12_31_33_45(struct FrameNeedEffectState *,
                                                       struct FrameObject *);

#endif
