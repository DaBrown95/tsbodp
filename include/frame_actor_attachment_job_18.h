#ifndef FRAME_ACTOR_ATTACHMENT_JOB_18_H
#define FRAME_ACTOR_ATTACHMENT_JOB_18_H

#include "display_actor_interaction.h"
#include "frame_actor_target_jobs.h"
#include "display_need_effect_lifecycle.h"

unsigned int frame_step_attachment_job_18(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_initialize_attachment_job_18(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_job_18(struct FrameNeedEffectState *, unsigned char *);
/* EC formal roles remain inferred until its generic caller is identified. */
unsigned int frame_prepare_attachment_job_18(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_begin_attachment_job_18(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_job_18(struct FrameNeedEffectState *, struct FrameObject *);
void frame_finish_attachment_job_18(struct FrameNeedEffectState *);

#endif
