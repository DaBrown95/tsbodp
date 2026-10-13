#ifndef FRAME_NEED_EFFECT_OPTIONAL_ACTIVITY_H
#define FRAME_NEED_EFFECT_OPTIONAL_ACTIVITY_H

#include "frame_need_effect_optional_jobs.h"

unsigned char frame_need_effect_try_reset_timer(struct FrameNeedEffectState *,
                                                 struct FrameObject *);
unsigned int frame_step_optional_activity_attachment_job(struct FrameNeedEffectState *,
                                                         struct FrameActorAttachmentRecord *);
unsigned int frame_dispatch_optional_activity_attachment_job(struct FrameNeedEffectState *,
                                                             struct FrameObject *);
/* Connected child handlers selected by the activity dispatcher. */
unsigned int frame_step_optional_attachment_kind_12(struct FrameNeedEffectState *,
                                                    struct FrameActorAttachmentRecord *);
unsigned int frame_step_optional_attachment_kind_45(struct FrameNeedEffectState *,
                                                    struct FrameActorAttachmentRecord *);
unsigned int frame_step_optional_attachment_kind_22(struct FrameNeedEffectState *,
                                                    struct FrameActorAttachmentRecord *);

#endif
