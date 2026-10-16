#ifndef FRAME_ACTOR_ATTACHMENT_JOBS_42_94_CALLBACKS_H
#define FRAME_ACTOR_ATTACHMENT_JOBS_42_94_CALLBACKS_H
#include "frame_actor_attachment_jobs_42_94.h"
unsigned int frame_select_attachment_jobs_42_94(struct FrameNeedEffectState *,unsigned char *);
unsigned int frame_begin_attachment_jobs_42_94(struct FrameNeedEffectState *,struct FrameObject *,unsigned int);

/* EC action switch; formal roles remain inferred until its consumer is identified. */
unsigned int frame_prepare_attachment_jobs_42_94(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);

#endif
