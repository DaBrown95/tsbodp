#ifndef FRAME_NEED_EFFECT_OPTIONAL_JOBS_H
#define FRAME_NEED_EFFECT_OPTIONAL_JOBS_H

#include "frame_need_effect_optional_state.h"
#include "frame_actor_attachment_parameters.h"

/* These jobs share the existing indicator/sample work view. Their result
 * words are observed as one while active and two on completion. */
unsigned int frame_need_effect_consume_optional(struct FrameNeedEffectState *,
                                                struct FrameActorAttachmentRecord *,
                                                struct FrameObject *);
unsigned int frame_step_optional_attachment_job(struct FrameNeedEffectState *,
                                                struct FrameActorAttachmentRecord *);
unsigned int frame_step_optional_animation_attachment_job(struct FrameNeedEffectState *,
                                                          struct FrameActorAttachmentRecord *);

/* Row-one definition callbacks select and dispatch attachment kinds 29/45.
 * The parameter predicate returns a word; its caller observes the low byte. */
unsigned int frame_need_effect_optional_one_ready(struct FrameNeedEffectState *);
unsigned int frame_select_optional_attachment_kind(struct FrameNeedEffectState *,
                                                   unsigned char *);
unsigned int frame_begin_optional_attachment_job(struct FrameNeedEffectState *,
                                                 struct FrameObject *, unsigned int);
unsigned int frame_dispatch_optional_attachment_job(struct FrameNeedEffectState *,
                                                    struct FrameObject *);
unsigned int frame_check_optional_attachment_capacity(struct FrameNeedEffectState *,
                                                       struct FrameObject *);

#endif
