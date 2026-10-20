#ifndef FRAME_ACTOR_ATTACHMENT_JOB_68_H
#define FRAME_ACTOR_ATTACHMENT_JOB_68_H

#include "frame_actor_attachment_counter_choices.h"
#include "resource_commands.h"

/* Byte observed by the kind-68 refresh callback; other writers remain open. */
extern unsigned char g_attachment_job_68_refresh_clock;
unsigned int frame_step_attachment_job_68(struct FrameNeedEffectState *,
                                         struct FrameActorAttachmentRecord *);
unsigned int frame_dispatch_attachment_job_68(struct FrameNeedEffectState *,
                                             struct FrameObject *);
void frame_finish_attachment_job_68(struct FrameNeedEffectState *);
unsigned int frame_initialize_attachment_job_68(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_job_68(struct FrameNeedEffectState *,
                                           unsigned char *);
/* Native R2 is the full-word kind; unused formal roles and generic delivery
 * remain provisional. */
unsigned int frame_prepare_attachment_job_68(struct FrameNeedEffectState *,
                                            struct FrameObject *, unsigned int);

#endif
