#ifndef FRAME_ACTOR_ATTACHMENT_JOBS_79_80_H
#define FRAME_ACTOR_ATTACHMENT_JOBS_79_80_H

#include "frame_need_effect_optional_jobs.h"
#include "frame_actor_state.h"

extern unsigned short g_frame_attachment_jobs_79_80_cues[6];

unsigned int frame_step_attachment_jobs_79_80(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *, unsigned char);
unsigned int frame_initialize_attachment_jobs_79_80(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_jobs_79_80(struct FrameNeedEffectState *, unsigned char *);
/* EC formal roles are inferred from the independently matched family. */
unsigned int frame_prepare_attachment_jobs_79_80(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_begin_attachment_jobs_79_80(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_jobs_79_80(struct FrameNeedEffectState *, struct FrameObject *);
void frame_finish_attachment_jobs_79_80(struct FrameNeedEffectState *);

/* Separate neighbouring entries; no installed callback role is established. */
unsigned int frame_check_attachment_jobs_79_80(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_attachment_jobs_79_80_default_value(void);

#endif
