#ifndef FRAME_OPTIONAL_ATTACHMENT_DISPATCH_H
#define FRAME_OPTIONAL_ATTACHMENT_DISPATCH_H

struct FrameNeedEffectState;
struct FrameObject;
struct FrameActorAttachmentRecord;

/* Names and runtime input populations remain provisional. */
unsigned int frame_dispatch_optional_attachment_288b4(struct FrameNeedEffectState *,
    struct FrameObject *);
unsigned int frame_step_optional_attachment_kind_12_28988(struct FrameNeedEffectState *,
    struct FrameActorAttachmentRecord *);
unsigned int frame_step_optional_attachment_kind_45_28378(struct FrameNeedEffectState *,
    struct FrameActorAttachmentRecord *);

/* Row-two callbacks. The initializer's observed word result is ignored by
 * the spawn adapter; tick is called with the state pointer. Generic EC delivery
 * and the prepare entry's unused owner/actor roles remain provisional. */
unsigned int frame_optional_attachment_initialize_28738(struct FrameNeedEffectState *);
unsigned int frame_prepare_optional_attachment_287d8(struct FrameNeedEffectState *,
    struct FrameObject *, unsigned int);
unsigned int frame_begin_optional_direction_attachment_28880(struct FrameNeedEffectState *,
    struct FrameObject *, unsigned int);
void frame_optional_attachment_tick_28984(struct FrameNeedEffectState *);

/* Shared worker for kinds 28, 30, 31, 32 and 33. */
unsigned int frame_step_optional_attachment_28424(struct FrameNeedEffectState *,
    struct FrameActorAttachmentRecord *);

#endif
