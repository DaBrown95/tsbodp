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

#endif
