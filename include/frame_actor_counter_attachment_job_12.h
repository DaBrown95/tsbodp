#ifndef FRAME_ACTOR_COUNTER_ATTACHMENT_JOB_12_H
#define FRAME_ACTOR_COUNTER_ATTACHMENT_JOB_12_H

#include "frame_actor_attachment_parameters.h"

unsigned int frame_initialize_counter_attachment_job_12(struct FrameNeedEffectState *);
/* The selector writes only the zero sentinel; it does not emit kind12. */
unsigned int frame_clear_counter_attachment_choices(struct FrameNeedEffectState *, unsigned char *);
unsigned int frame_begin_counter_attachment_job_12(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_counter_attachment_job_12(struct FrameNeedEffectState *, struct FrameObject *);
void frame_finish_counter_attachment_job_12(struct FrameNeedEffectState *);
unsigned int frame_step_counter_attachment_job_12(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);

/* Separate neighbouring entries; no installed callback roles are established. */
unsigned int frame_check_counter_attachment_job_12(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_counter_attachment_default_zero(void);

#endif
