#ifndef FRAME_ACTOR_ATTACHMENT_JOBS_42_94_H
#define FRAME_ACTOR_ATTACHMENT_JOBS_42_94_H
#include "frame_actor_attachment_parameters.h"
#include "frame_actor_social.h"
#include "scene.h"
/* Actual signed-index*4 + byte-zero read; complete row capacity is unknown. */
extern const unsigned char g_attachment_job_94_sequence_rows[][4];
unsigned int frame_step_attachment_job_42(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
unsigned int frame_step_attachment_job_94(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
unsigned int frame_dispatch_attachment_jobs_42_94(struct FrameNeedEffectState *,struct FrameObject *);
#endif
