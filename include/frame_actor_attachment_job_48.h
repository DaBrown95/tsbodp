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
/* Actual observed row102 definition callbacks for kind48. */
unsigned int frame_initialize_attachment_job_48(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_job_48(struct FrameNeedEffectState *, unsigned char *);
/* EC formal roles remain inferred until its generic caller is identified. */
unsigned int frame_prepare_attachment_job_48(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
void frame_finish_attachment_job_48(struct FrameNeedEffectState *);

/* Separate neighbouring entries; no installed callback role is established. */
unsigned int frame_check_attachment_job_48(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_attachment_job_48_default_value(void);

#endif
