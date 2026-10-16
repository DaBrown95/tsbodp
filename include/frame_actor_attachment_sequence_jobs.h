#ifndef FRAME_ACTOR_ATTACHMENT_SEQUENCE_JOBS_H
#define FRAME_ACTOR_ATTACHMENT_SEQUENCE_JOBS_H

#include "frame_need_effect_optional_jobs.h"
#include "scene.h"

unsigned int frame_initialize_attachment_sequence_jobs(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_sequence_jobs(struct FrameNeedEffectState *, unsigned char *);
/* EC consumes the third word; unused first-two roles remain provisional. */
unsigned int frame_check_attachment_sequence_jobs(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_begin_attachment_sequence_jobs(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
void frame_finish_attachment_sequence_jobs(struct FrameNeedEffectState *);

unsigned int frame_dispatch_attachment_sequence_jobs(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_step_attachment_sequence_job_45_41794(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_step_attachment_sequence_job_18_41840(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_step_attachment_sequence_modes_56_57(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *, unsigned int);
unsigned int frame_step_attachment_sequence_modes_2_5(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *, unsigned int);
void frame_refresh_attachment_sequence_41c18(struct FrameNeedEffectState *);


/* Separate neighbouring predicate; no installed callback slot is identified. */
unsigned int frame_check_attachment_sequence_count(struct FrameNeedEffectState *, struct FrameObject *);

#endif
