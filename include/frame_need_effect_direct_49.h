#ifndef FRAME_NEED_EFFECT_DIRECT_49_H
#define FRAME_NEED_EFFECT_DIRECT_49_H
struct FrameNeedEffectState;struct FrameObject;struct FrameActorAttachmentRecord;
unsigned int frame_need_effect_direct_49_check(struct FrameNeedEffectState *,struct FrameObject *);
unsigned int frame_need_effect_direct_49_choices(struct FrameNeedEffectState *,unsigned char *);
unsigned int frame_need_effect_direct_49_begin(struct FrameNeedEffectState *,struct FrameObject *,unsigned int);
unsigned int frame_need_effect_direct_49_dispatch(struct FrameNeedEffectState *,struct FrameObject *);
unsigned int frame_need_effect_direct_49_step(struct FrameNeedEffectState *,struct FrameActorAttachmentRecord *);

/* EC action switches; unused formal roles remain inferred. */
unsigned int frame_prepare_need_effect_direct_49(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);

#endif
