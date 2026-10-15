#ifndef FRAME_ACTOR_ATTACHMENT_JOB_48_H
#define FRAME_ACTOR_ATTACHMENT_JOB_48_H
#include "frame_actor_attachment_parameters.h"
/* Existing accepted scalar APIs; declarations preserve the actual definitions. */
int frame_read_signed_parameter(const void *, unsigned int);
int frame_actor_need_fixed_word(struct FrameActorNeedState *, unsigned int);
/* Actual word-stride read at 08046764..08046770; capacity remains unproved. */
extern const unsigned int g_attachment_job_48_direction_words[];
unsigned int frame_begin_attachment_job_48(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_step_attachment_job_48(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_dispatch_attachment_job_48(struct FrameNeedEffectState *, struct FrameObject *);
#endif
