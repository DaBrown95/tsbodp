#ifndef FRAME_ACTOR_ATTACHMENT_JOB_26_H
#define FRAME_ACTOR_ATTACHMENT_JOB_26_H

#include "display_actor_interaction.h"
#include "frame_random.h"
#include "scene_request_queue.h"

unsigned int frame_initialize_attachment_job_26(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_job_26(struct FrameNeedEffectState *, unsigned char *);
/* EC formal roles remain inferred until its generic caller is identified. */
unsigned int frame_prepare_attachment_job_26(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_begin_attachment_job_26(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_dispatch_attachment_job_26(struct FrameNeedEffectState *, struct FrameObject *);
void frame_finish_attachment_job_26(struct FrameNeedEffectState *);
unsigned int frame_step_attachment_job_26(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);

/* Separate neighbouring entry; no installed callback role is established. */
unsigned int frame_check_attachment_job_26(struct FrameNeedEffectState *, struct FrameObject *);

#endif
