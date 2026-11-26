#ifndef FRAME_OPTIONAL_ATTACHMENT_DISPATCH_H
#define FRAME_OPTIONAL_ATTACHMENT_DISPATCH_H

struct FrameNeedEffectState;
struct FrameObject;
struct FrameActorAttachmentRecord;

/* Names and runtime input populations remain provisional. */
unsigned int frame_dispatch_optional_attachment_kinds_12_28_45(struct FrameNeedEffectState *,
                                                      struct FrameObject *);
unsigned int frame_step_optional_attachment_kind_12_keep_direction(struct FrameNeedEffectState *,
                                                          struct FrameActorAttachmentRecord *);
unsigned int frame_step_optional_attachment_kind_45_actor_effect_anim_45(struct FrameNeedEffectState *,
                                                          struct FrameActorAttachmentRecord *);

/* Row-two callbacks. The initializer's observed word result is ignored by
 * the spawn adapter; tick is called with the state pointer. Generic EC delivery
 * and the prepare entry's unused owner/actor roles remain provisional. */
unsigned int frame_optional_attachment_initialize(struct FrameNeedEffectState *);
unsigned int frame_prepare_optional_attachment_kinds_12_to_45(struct FrameNeedEffectState *,
                                                     struct FrameObject *, unsigned int);
unsigned int frame_begin_optional_direction_attachment(struct FrameNeedEffectState *,
                                                             struct FrameObject *, unsigned int);
void frame_optional_attachment_tick(struct FrameNeedEffectState *);

/* Shared worker for kinds 28, 30, 31, 32 and 33. */
unsigned int frame_step_optional_attachment_kinds_28_30_to_33(struct FrameNeedEffectState *,
                                                  struct FrameActorAttachmentRecord *);

#endif
