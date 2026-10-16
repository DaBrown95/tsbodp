#ifndef FRAME_ACTOR_ATTACHMENT_JOB_49_H
#define FRAME_ACTOR_ATTACHMENT_JOB_49_H
#include "frame_need_effect_optional_jobs.h"

/* Remaining callbacks for the shared definition rows observed at 56/58.
 * Worker, begin and dispatch declarations already live in target_jobs.h. */
unsigned int frame_initialize_attachment_job_49(struct FrameNeedEffectState *);
/* Separate neighbouring predicate; no installed callback role is established. */
unsigned int frame_check_attachment_job_49_count(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_select_attachment_job_49(struct FrameNeedEffectState *, unsigned char *);
/* EC unused formal roles remain inferred until its generic consumer is found. */
unsigned int frame_prepare_attachment_job_49(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
void frame_tick_attachment_job_49(struct FrameNeedEffectState *);
#endif
