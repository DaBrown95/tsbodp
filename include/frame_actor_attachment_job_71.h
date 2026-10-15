#ifndef FRAME_ACTOR_ATTACHMENT_JOB_71_H
#define FRAME_ACTOR_ATTACHMENT_JOB_71_H
#include "frame_actor_attachment_parameters.h"
#include "frame_actor_social.h"
/* Existing signed word reader; same definition qualified for the sibling jobs. */
int frame_actor_need_fixed_word(struct FrameActorNeedState *, unsigned int);
unsigned int frame_begin_attachment_job_71(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_step_attachment_job_71(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_dispatch_attachment_job_71(struct FrameNeedEffectState *, struct FrameObject *);
#endif
