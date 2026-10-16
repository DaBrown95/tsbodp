#ifndef FRAME_ACTOR_ATTACHMENT_JOB_12_H
#define FRAME_ACTOR_ATTACHMENT_JOB_12_H
#include "frame_actor_attachment_parameters.h"
#include "frame_actor_state.h"

/* Row135's two observed word timers; this is an access view of existing state. */
struct FrameAttachmentJob12Timers {
    unsigned char unknown00[0x64];
    int idle_timer, active_timer;
};
unsigned int frame_step_attachment_job_12_34bf4(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_initialize_attachment_job_12(struct FrameNeedEffectState *);
unsigned int frame_check_attachment_job_12(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_select_attachment_job_12(struct FrameNeedEffectState *, unsigned char *);
/* Unused EC formal roles remain inferred until its generic consumer is known. */
unsigned int frame_prepare_attachment_job_12(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_begin_attachment_job_12(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_job_12(struct FrameNeedEffectState *, struct FrameObject *);
void frame_tick_attachment_job_12(struct FrameNeedEffectState *);
unsigned int frame_attachment_job_12_default_value(void);
#endif
