#ifndef FRAME_ACTOR_ATTACHMENT_JOB_71_H
#define FRAME_ACTOR_ATTACHMENT_JOB_71_H
#include "frame_actor_attachment_parameters.h"
#include "frame_actor_social.h"
/* Existing signed word reader; same definition qualified for the sibling jobs. */
int frame_actor_need_fixed_word(struct FrameActorNeedState *, unsigned int);
unsigned int frame_begin_attachment_job_71(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_step_attachment_job_71(struct FrameNeedEffectState *, struct FrameActorAttachmentRecord *);
unsigned int frame_dispatch_attachment_job_71(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_initialize_attachment_job_71(struct FrameNeedEffectState *);
unsigned int frame_select_attachment_job_71(struct FrameNeedEffectState *, unsigned char *);
void frame_finish_attachment_job_71(struct FrameNeedEffectState *);

/* Separate entries; no installed table-callback role is established. */
unsigned int frame_check_attachment_job_71(struct FrameNeedEffectState *, struct FrameObject *);
unsigned int frame_attachment_job_71_default_value(void);


/* EC action switch; formal roles remain inferred until its consumer is identified. */
unsigned int frame_prepare_attachment_job_71(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);

#endif
