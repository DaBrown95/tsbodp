#ifndef FRAME_SPECIAL_NEED_JOBS_H
#define FRAME_SPECIAL_NEED_JOBS_H
#include "frame_need_effect_optional_activity.h"
#include "frame_actor_social.h"
#include "frame_actor_target_jobs.h"

/* Definition row141 selects jobs7/45. The actor timer here is a signed word
 * at +0x58, distinct from the halfword need_timer used by other job families. */
unsigned int frame_initialize_special_need_jobs(struct FrameNeedEffectState *);
unsigned int frame_check_special_need_actor(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_select_special_need_jobs(struct FrameNeedEffectState *, unsigned char *);
/* Formal roles follow the related EC action-switch family; its consumer is open. */
unsigned int frame_prepare_special_need_jobs(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_begin_special_need_jobs(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_special_need_jobs(struct FrameNeedEffectState *, struct FrameObject *);
void frame_finish_special_need_jobs(struct FrameNeedEffectState *);
unsigned int frame_step_special_need_job_7(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_step_special_need_job_45(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
/* Unrooted adjacent constant-result body; no percentage/FC use is established. */
unsigned int frame_special_need_default_value(void);
#endif
