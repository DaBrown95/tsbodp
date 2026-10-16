#ifndef FRAME_ACTOR_ATTACHMENT_JOB_75_H
#define FRAME_ACTOR_ATTACHMENT_JOB_75_H
#include "frame_need_effect_optional_jobs.h"

/* Unrooted neighbouring source family. These entry roles/signatures are
 * inferred from its selector/status/worker layout; no installed row is known.
 * The already-owned route_3 retains its unsigned-char return contract. */
unsigned int frame_initialize_attachment_job_75(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_job_75(struct FrameNeedEffectState *, unsigned char *);
unsigned int frame_prepare_attachment_job_75(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_job_75(struct FrameNeedEffectState *, struct FrameObject *);
void frame_tick_attachment_job_75(struct FrameNeedEffectState *);
unsigned int frame_attachment_job_75_default_value(void);
unsigned int frame_step_attachment_job_75(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
#endif
