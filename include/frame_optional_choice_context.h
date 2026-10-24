#ifndef FRAME_OPTIONAL_CHOICE_CONTEXT_H
#define FRAME_OPTIONAL_CHOICE_CONTEXT_H

#include "frame_optional_choice_apply.h"

/* Bounded callback view. Definition byte +0x21 is copied to attachment_mode
 * at +0x60. Active is a byte at +0x64, tested specifically against one.
 * This view does not change the established need-effect state layout. */
struct FrameOptionalChoiceContextState {
    unsigned char unknown_00[0x60];
    unsigned char attachment_mode;
    unsigned char unknown_61[3];
    unsigned char active;
};

unsigned char frame_object_has_zero_id(struct FrameObject *);
unsigned int frame_initialize_optional_choice_context(struct FrameNeedEffectState *);
unsigned int frame_optional_choice_context_available(struct FrameNeedEffectState *,
                                                      struct FrameObject *);
unsigned int frame_select_optional_choice_attachment_kind(struct FrameNeedEffectState *,
                                                           unsigned char *);
/* The modeled 41/45 kind switch reproduces the saved argument across the
 * byte-result predicate call. Historical cases and EC delivery remain inferred. */
unsigned int frame_check_optional_choice_attachment_kind(struct FrameNeedEffectState *,
                                                          struct FrameObject *, unsigned int);
unsigned int frame_begin_optional_choice_attachment_job(struct FrameNeedEffectState *,
                                                         struct FrameObject *, unsigned int);
unsigned int frame_dispatch_optional_choice_attachment_job(struct FrameNeedEffectState *,
                                                            struct FrameObject *);
unsigned int frame_step_optional_choice_kind_45(struct FrameNeedEffectState *,
                                                struct FrameActorAttachmentRecord *);
void frame_optional_choice_context_tick(struct FrameNeedEffectState *);

#endif
