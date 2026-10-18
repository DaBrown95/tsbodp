#ifndef FRAME_OPTIONAL_ATTACHMENT_JOBS_12_45_59_H
#define FRAME_OPTIONAL_ATTACHMENT_JOBS_12_45_59_H

#include "frame_need_effect_optional_completion.h"

/* Observed row-92 action codes; names and original typedef remain provisional. */
enum FrameOptionalAttachmentKind12_45_59 {
    FRAME_OPTIONAL_ATTACHMENT_KIND_12 = 12,
    FRAME_OPTIONAL_ATTACHMENT_KIND_45 = 45,
    FRAME_OPTIONAL_ATTACHMENT_KIND_59 = 59
};

unsigned int frame_step_optional_attachment_kind_12_45fb4(struct FrameNeedEffectState *,
                                                        struct FrameActorAttachmentRecord *);
unsigned int frame_step_optional_attachment_kind_45_46050(struct FrameNeedEffectState *,
                                                        struct FrameActorAttachmentRecord *);
unsigned int frame_step_optional_attachment_kind_59(struct FrameNeedEffectState *,
                                                   struct FrameActorAttachmentRecord *);
unsigned int frame_dispatch_optional_attachment_kinds_12_45_59(struct FrameNeedEffectState *,
                                                              struct FrameObject *);

/* The initializer's unused owner/word result are chosen roles; its caller
 * ignores that result. F8 is called through the existing void(state) contract. */
unsigned int frame_initialize_optional_attachment_kinds_12_45_59(struct FrameNeedEffectState *);
void frame_finish_optional_attachment_kinds_12_45_59(struct FrameNeedEffectState *);

#endif
