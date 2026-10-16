#ifndef FRAME_PARAMETER_STAGE_JOBS_H
#define FRAME_PARAMETER_STAGE_JOBS_H
#include "frame_need_effect_optional_activity.h"
#include "frame_actor_social.h"
#include "frame_actor_target_jobs.h"

/* Row31 selects job7 or91 from its signed halfword parameter. The shared actor
 * need_timer here is the halfword at+0x5E; names describe this bounded path. */
unsigned int frame_initialize_parameter_stage_jobs(struct FrameNeedEffectState *);
unsigned int frame_check_parameter_stage_actor(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_select_parameter_stage_jobs(struct FrameNeedEffectState *, unsigned char *);
/* EC formal roles remain inferred until its generic consumer is recovered. */
unsigned int frame_prepare_parameter_stage_jobs(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_begin_parameter_stage_jobs(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_parameter_stage_jobs(struct FrameNeedEffectState *, struct FrameObject *);
void frame_finish_parameter_stage_jobs(struct FrameNeedEffectState *);
unsigned int frame_parameter_stage_percentage(struct FrameNeedEffectState *);
unsigned int frame_step_parameter_stage_job_7(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_step_parameter_stage_job_91(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
#endif
