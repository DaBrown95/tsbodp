#ifndef FRAME_ACTOR_ATTACHMENT_JOB_24_H
#define FRAME_ACTOR_ATTACHMENT_JOB_24_H

#include "frame_need_effect_optional_jobs.h"

unsigned int frame_step_attachment_job_24(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_initialize_attachment_job_24(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_job_24(struct FrameNeedEffectState *, unsigned char *);
/* EC formal roles are inferred; its generic caller remains unidentified. */
unsigned int frame_prepare_attachment_job_24(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_begin_attachment_job_24(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_job_24(struct FrameNeedEffectState *, struct FrameObject *);
void frame_finish_attachment_job_24(struct FrameNeedEffectState *);

/* Separate neighbouring predicate; no installed callback role is established. */
unsigned int frame_check_attachment_job_24(struct FrameNeedEffectState *, struct FrameObject *);

#endif
