#ifndef FRAME_ACTOR_ATTACHMENT_JOBS_60_63_H
#define FRAME_ACTOR_ATTACHMENT_JOBS_60_63_H
#include "frame_need_effect_optional_jobs.h"

/* Local work bytes used by the shared definitions observed at rows 14/15/19. */
struct FrameAttachmentRecoveryWork {
    unsigned char unknown00[0x64];
    unsigned short countdown;
    unsigned char unknown66[2], settled;
};
void frame_tick_attachment_jobs_60_63(struct FrameNeedEffectState *);
unsigned int frame_step_attachment_job_60(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_step_attachment_job_63(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_initialize_attachment_jobs_60_63(struct FrameNeedEffectState *);
/* Separate neighbouring predicate; no installed callback role is established. */
unsigned int frame_check_attachment_jobs_60_63_count(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_select_attachment_jobs_60_63(struct FrameNeedEffectState *, unsigned char *);
/* EC formal roles remain inferred until its generic consumer is identified. */
unsigned int frame_prepare_attachment_jobs_60_63(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_begin_attachment_jobs_60_63(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_jobs_60_63(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_attachment_jobs_60_63_percentage(struct FrameNeedEffectState *);
#endif
