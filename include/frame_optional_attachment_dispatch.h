#ifndef FRAME_OPTIONAL_ATTACHMENT_DISPATCH_H
#define FRAME_OPTIONAL_ATTACHMENT_DISPATCH_H

struct FrameNeedEffectState;
struct FrameObject;
struct FrameActorAttachmentRecord;

/* Names and incoming roots remain provisional. */
unsigned int frame_dispatch_optional_attachment_288b4(struct FrameNeedEffectState *,
    struct FrameObject *);
unsigned int frame_step_optional_attachment_kind_12_28988(struct FrameNeedEffectState *,
    struct FrameActorAttachmentRecord *);
unsigned int frame_step_optional_attachment_kind_45_28378(struct FrameNeedEffectState *,
    struct FrameActorAttachmentRecord *);

/* Explicit original-code dependency; this worker remains unconverted. */
unsigned int frame_step_optional_attachment_28424(struct FrameNeedEffectState *,
    struct FrameActorAttachmentRecord *);

#endif
