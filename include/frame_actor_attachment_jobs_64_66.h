#ifndef FRAME_ACTOR_ATTACHMENT_JOBS_64_66_H
#define FRAME_ACTOR_ATTACHMENT_JOBS_64_66_H

#include "frame_actor_attachment_job_87.h"
#include "resource_actor_entries.h"

unsigned int frame_step_attachment_jobs_64_65(struct FrameNeedEffectState *,
                                               struct FrameActorAttachmentRecord *);
unsigned int frame_step_attachment_job_66(struct FrameNeedEffectState *,
                                          struct FrameActorAttachmentRecord *);
unsigned int frame_begin_attachment_jobs_64_66(struct FrameNeedEffectState *,
                                                struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_jobs_64_66(struct FrameNeedEffectState *,
                                                   struct FrameObject *);

#endif
