#ifndef FRAME_ACTOR_ATTACHMENT_JOBS_45_90_H
#define FRAME_ACTOR_ATTACHMENT_JOBS_45_90_H
#include "frame_need_effect_optional_jobs.h"
#include "frame_actor_social.h"
#include "resource_conditions.h"
unsigned int frame_initialize_attachment_jobs_45_90(struct FrameNeedEffectState *);
unsigned int frame_check_attachment_jobs_45_90_count(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_select_attachment_job_90(struct FrameNeedEffectState *, unsigned char *);
unsigned int frame_prepare_attachment_jobs_45_90(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_begin_attachment_jobs_45_90(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_jobs_45_90(struct FrameNeedEffectState *, struct FrameObject *);
void frame_finish_attachment_jobs_45_90(struct FrameNeedEffectState *);
unsigned int frame_step_attachment_jobs_45_90(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
#endif
