#ifndef FRAME_ACTOR_ATTACHMENT_JOB_70_H
#define FRAME_ACTOR_ATTACHMENT_JOB_70_H

#include "frame_actor_attachment_parameters.h"
#include "frame_actor_social.h"

unsigned int frame_step_attachment_job_70(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_initialize_attachment_job_70(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_job_70(struct FrameNeedEffectState *, unsigned char *);
/* EC formal roles remain inferred until its generic caller is identified. */
unsigned int frame_prepare_attachment_job_70(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_begin_attachment_job_70(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_job_70(struct FrameNeedEffectState *, struct FrameObject *);
void frame_finish_attachment_job_70(struct FrameNeedEffectState *);

/* Separate neighbouring entries; no installed callback roles are established. */
unsigned int frame_check_attachment_job_70(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_attachment_job_70_default_value(void);

#endif
