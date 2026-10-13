#ifndef FRAME_NEED_EFFECT_OPTIONAL_COMPLETION_H
#define FRAME_NEED_EFFECT_OPTIONAL_COMPLETION_H

#include "frame_need_effect_optional_activity.h"

/* Mode consumers observe the parameter as both unsigned and signed halfwords. */
unsigned int frame_need_effect_consume_optional_two(struct FrameNeedEffectState *);
unsigned int frame_need_effect_consume_optional_three(struct FrameNeedEffectState *);
unsigned char frame_need_effect_optional_percentage(struct FrameNeedEffectState *);

/* The first argument of the parameter step is unused in the observed body. */
unsigned int frame_need_effect_step_parameter(struct FrameNeedEffectState *, void *,
                                              unsigned int, struct FrameObject *);
unsigned int frame_step_optional_parameter_attachment_job(struct FrameNeedEffectState *,
                                                          struct FrameActorAttachmentRecord *);
unsigned int frame_step_optional_attachment_kind_7(struct FrameNeedEffectState *,
                                                  struct FrameActorAttachmentRecord *);
unsigned int frame_select_optional_parameter_attachment_kind(struct FrameNeedEffectState *,
                                                             unsigned char *);
unsigned int frame_check_optional_parameter_attachment_kind(struct FrameNeedEffectState *,
                                                            struct FrameObject *, unsigned int);
unsigned int frame_begin_optional_parameter_attachment_job(struct FrameNeedEffectState *,
                                                           struct FrameObject *, unsigned int);
unsigned int frame_dispatch_optional_parameter_attachment_job(struct FrameNeedEffectState *,
                                                              struct FrameObject *);

#endif
