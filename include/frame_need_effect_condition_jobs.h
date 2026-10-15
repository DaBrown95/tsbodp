#ifndef FRAME_NEED_EFFECT_CONDITION_JOBS_H
#define FRAME_NEED_EFFECT_CONDITION_JOBS_H
struct FrameNeedEffectState;
struct FrameObject;
struct FrameActorAttachmentRecord;
unsigned int frame_need_effect_check_condition_jobs(struct FrameNeedEffectState *,struct FrameObject *);
unsigned int frame_need_effect_select_condition_jobs(struct FrameNeedEffectState *,unsigned char *);
unsigned int frame_need_effect_begin_condition_job(struct FrameNeedEffectState *,struct FrameObject *,unsigned int);
unsigned int frame_need_effect_dispatch_condition_job(struct FrameNeedEffectState *,struct FrameObject *);
unsigned int frame_step_condition_need_job(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
unsigned int frame_step_condition_parameter_job(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
unsigned int frame_step_condition_wait_job(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
#endif
