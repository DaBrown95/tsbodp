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

/* Actual observed rows16/17 definition callbacks. */
unsigned int frame_initialize_attachment_job_72(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_job_72(struct FrameNeedEffectState *, unsigned char *);
/* EC formal roles remain inferred until its generic caller is identified. */
unsigned int frame_prepare_attachment_job_72(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
void frame_finish_attachment_job_72(struct FrameNeedEffectState *);

/* Separate neighbouring entries; no installed callback role is established. */
unsigned int frame_check_attachment_job_72(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_attachment_job_72_default_value(void);

#endif
