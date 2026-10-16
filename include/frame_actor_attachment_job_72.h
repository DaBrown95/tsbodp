#ifndef FRAME_ACTOR_ATTACHMENT_JOB_72_H
#define FRAME_ACTOR_ATTACHMENT_JOB_72_H

#include "frame_actor_attachment_job_87.h"

/* Kind 72 uses the existing bounded mode/parameter world and record APIs. */
unsigned int frame_step_attachment_job_72(struct FrameNeedEffectState *,
                                          struct FrameActorAttachmentRecord *);
unsigned int frame_begin_attachment_job_72(struct FrameNeedEffectState *,
                                           struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_job_72(struct FrameNeedEffectState *,
                                              struct FrameObject *);

#endif
