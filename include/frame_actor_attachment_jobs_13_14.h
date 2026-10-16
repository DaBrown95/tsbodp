#ifndef FRAME_ACTOR_ATTACHMENT_JOBS_13_14_H
#define FRAME_ACTOR_ATTACHMENT_JOBS_13_14_H
#include "frame_need_effect_optional_jobs.h"

/* Row zero's observed writer exposes actions13/14. Callback formals remain
 * inferred; the generic EC consumer has not been identified. */
unsigned int frame_initialize_attachment_jobs_13_14(struct FrameNeedEffectState *);
unsigned int frame_check_attachment_jobs_13_14_count(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_select_attachment_jobs_13_14(struct FrameNeedEffectState *, unsigned char *);
unsigned int frame_prepare_attachment_jobs_13_14(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_begin_attachment_jobs_13_14(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_jobs_13_14(struct FrameNeedEffectState *, struct FrameObject *);
void frame_finish_attachment_jobs_13_14(struct FrameNeedEffectState *);
unsigned int frame_attachment_jobs_13_14_percentage(struct FrameNeedEffectState *);
unsigned int frame_step_attachment_jobs_13_14(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
#endif
