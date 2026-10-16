#ifndef FRAME_ACTOR_ATTACHMENT_JOBS_45_56_57_H
#define FRAME_ACTOR_ATTACHMENT_JOBS_45_56_57_H

#include "frame_need_effect_optional_jobs.h"
#include "frame_actor_target_routes.h"

/* Actual word at owner+64 read and written by this row106/107/108 family. */
struct FrameAttachmentAnimationChoice {
    unsigned char unknown00[0x64];
    unsigned int mode;
};
unsigned int frame_step_optional_attachment_job_45_23d00(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_step_attachment_modes_56_57_23ec4(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *, unsigned int);
unsigned int frame_initialize_attachment_jobs_45_56_57(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_jobs_45_56_57(struct FrameNeedEffectState *, unsigned char *);
/* The third EC word is retained; unused first-two formal roles remain inferred. */
unsigned int frame_prepare_attachment_jobs_45_56_57(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_begin_attachment_jobs_45_56_57(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_jobs_45_56_57(struct FrameNeedEffectState *, struct FrameObject *);
void frame_tick_attachment_jobs_45_56_57(struct FrameNeedEffectState *);
/* Separate neighbouring entries; no installed callback role is established. */
unsigned int frame_check_attachment_jobs_45_56_57(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_attachment_jobs_45_56_57_default_value(void);

#endif
