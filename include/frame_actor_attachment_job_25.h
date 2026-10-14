#ifndef FRAME_ACTOR_ATTACHMENT_JOB_25_H
#define FRAME_ACTOR_ATTACHMENT_JOB_25_H
#include "frame_actor_attachment_parameters.h"
int frame_read_signed_parameter(const void *,unsigned int);
struct FrameAttachmentNeedWordPrefix {int values[8];};
struct FrameAttachmentJob25Work {unsigned char unknown00[0x58];struct FrameObject *indicator;};
struct FrameAttachmentJob25Clock {unsigned char unknown00[0x58];int timer;};
int frame_actor_need_fixed_word(struct FrameActorNeedState *,unsigned int);
unsigned int frame_step_attachment_job_25(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);
unsigned int frame_dispatch_attachment_job_25(struct FrameNeedEffectState *,struct FrameObject *);
unsigned int frame_begin_attachment_job_25(struct FrameNeedEffectState *,struct FrameObject *,unsigned int);
unsigned int frame_initialize_attachment_job_25(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_job_25(struct FrameNeedEffectState *,unsigned char *);
void frame_finish_attachment_job_25(struct FrameNeedEffectState *);
#define JOB25_WORK(o) ((struct FrameAttachmentJob25Work *)(o))
#define JOB25_CLOCK(o) ((struct FrameAttachmentJob25Clock *)(o))
#endif
