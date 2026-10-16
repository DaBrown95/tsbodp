#ifndef FRAME_ACTOR_ATTACHMENT_JOB_43_H
#define FRAME_ACTOR_ATTACHMENT_JOB_43_H
#include "frame_need_effect_optional_jobs.h"

unsigned int frame_step_attachment_job_43(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_initialize_attachment_job_43(struct FrameNeedEffectState *);
/* Separate adjacent predicate; no installed callback role is established. */
unsigned int frame_check_attachment_job_43_count(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_select_attachment_job_43(struct FrameNeedEffectState *, unsigned char *);
/* EC unused formal roles remain inferred until its generic consumer is found. */
unsigned int frame_prepare_attachment_job_43(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_begin_attachment_job_43(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_job_43(struct FrameNeedEffectState *, struct FrameObject *);
void frame_tick_attachment_job_43(struct FrameNeedEffectState *);
/* Adjacent unrooted leaf; row40's FC pointer is null. */
unsigned int frame_attachment_job_43_default_value(void);
#endif
