#ifndef FRAME_ACTOR_ATTACHMENT_TIMED_JOB_12_H
#define FRAME_ACTOR_ATTACHMENT_TIMED_JOB_12_H
#include "frame_actor_attachment_jobs.h"
#include "frame_actor_state.h"
unsigned int frame_initialize_timed_attachment_job_12(struct FrameNeedEffectState *);
unsigned int frame_select_timed_attachment_job_12(struct FrameNeedEffectState *,unsigned char *);
/* Unused EC formal roles remain inferred until its generic consumer is known. */
unsigned int frame_prepare_timed_attachment_job_12(struct FrameNeedEffectState *,struct FrameObject *,unsigned int);
unsigned int frame_begin_timed_attachment_job_12(struct FrameNeedEffectState *,struct FrameObject *,unsigned int);
unsigned int frame_dispatch_timed_attachment_job_12(struct FrameNeedEffectState *,struct FrameObject *);
void frame_tick_timed_attachment_job_12(struct FrameNeedEffectState *);
/* Separate neighbouring entry; both observed definition FC pointers are null. */
unsigned int frame_timed_attachment_job_12_default_value(void);
unsigned int frame_step_timed_attachment_job_12(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
#endif
