#ifndef FRAME_ACTOR_ATTACHMENT_CONTROL_JOBS_H
#define FRAME_ACTOR_ATTACHMENT_CONTROL_JOBS_H

#include "frame_need_effect_optional_jobs.h"
#include "scene.h"

unsigned int frame_initialize_attachment_control_jobs(struct FrameNeedEffectState *);
unsigned int frame_begin_attachment_control_jobs(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
void frame_finish_attachment_control_jobs(struct FrameNeedEffectState *);
unsigned int frame_dispatch_attachment_control_jobs(struct FrameNeedEffectState *, struct FrameObject *);
void frame_refresh_attachment_control_174a8(struct FrameNeedEffectState *);
unsigned int frame_step_attachment_job_45_17124(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_step_attachment_job_100_171c8(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_step_attachment_controls_56_57(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *, unsigned int);
unsigned int frame_step_attachment_controls_98_99_101(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *, unsigned int);


/* Separate neighbouring predicate; no installed callback slot is identified. */
unsigned int frame_check_attachment_control_jobs(struct FrameNeedEffectState *, struct FrameObject *);

#endif
