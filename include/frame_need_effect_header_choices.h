#ifndef FRAME_NEED_EFFECT_HEADER_CHOICES_H
#define FRAME_NEED_EFFECT_HEADER_CHOICES_H
struct FrameNeedEffectState;
struct FrameObject;
struct FrameActorAttachmentRecord;
struct FrameActorAttachmentOwner;
unsigned int frame_need_effect_check_actor_header_variant(struct FrameNeedEffectState *,struct FrameObject *);
unsigned int frame_need_effect_select_header_choices(struct FrameNeedEffectState *,unsigned char *);
struct FrameActorAttachmentRecord *frame_need_effect_nth_attachment(struct FrameActorAttachmentOwner *,unsigned int);

/* EC action switches; unused formal roles remain inferred. */
unsigned int frame_prepare_need_effect_header_choices(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);

#endif
