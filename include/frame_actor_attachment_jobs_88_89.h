#ifndef FRAME_ACTOR_ATTACHMENT_JOBS_88_89_H
#define FRAME_ACTOR_ATTACHMENT_JOBS_88_89_H

#include "frame_need_effect_optional_activity.h"
#include "frame_actor_social.h"

unsigned int frame_step_attachment_job_88(struct FrameNeedEffectState *,
                                          struct FrameActorAttachmentRecord *);

unsigned int frame_step_attachment_job_89(struct FrameNeedEffectState *,
                                          struct FrameActorAttachmentRecord *);
unsigned int frame_begin_attachment_jobs_88_89(struct FrameNeedEffectState *,
                                               struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_jobs_88_89(struct FrameNeedEffectState *,
                                                  struct FrameObject *);

#endif
