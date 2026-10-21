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

/* Observed definition rows 5--7: initializer and tick receive state; the
 * prepare callback consumes only kind. Other historical unused formals and
 * generic EC invocation populations remain provisional. */
unsigned int frame_optional_activity_initialize_437b0(struct FrameNeedEffectState *);
unsigned int frame_prepare_optional_activity_437dc(struct FrameNeedEffectState *,
    struct FrameObject *, unsigned int);
void frame_optional_activity_tick_439a4(struct FrameNeedEffectState *);

/* Independently bounded unrooted leaf: no inputs are consumed. The historical
 * unused argument list and original declaration remain unresolved. */
unsigned int frame_unrooted_optional_activity_hundred_439a8(void);

#endif
