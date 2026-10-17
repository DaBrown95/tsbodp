#ifndef FRAME_OPTIONAL_THREE_EFFECT_H
#define FRAME_OPTIONAL_THREE_EFFECT_H
#include "display_need_effect_lifecycle.h"
#include "audio_game.h"

/* Row41-specific state work. +65 is written, but its consumers remain unknown. */
struct FrameOptionalThreeEffectState {
 unsigned char unknown00[0x54]; struct FrameObject *object;
 unsigned char unknown58[12],active,field65,unknown66[0xe0-0x66];
 unsigned int sample_handle;
};
struct FrameOptionalThreeEffectObject {
 unsigned char unknown00[0x58]; int timer;
 unsigned char unknown5c[8]; struct FrameOptionalThreeEffectState *state;
 unsigned char unknown68[0x88-0x68]; void (*on_step)(struct FrameObject *);
};
struct FrameObject *frame_optional_choice_complete(unsigned int);
void frame_commit_need_effect(struct FrameObject *,unsigned int);
unsigned int frame_optional_three_effect_initialize(struct FrameNeedEffectState *);
/* The concrete mode-three producer passes two zero words; this body ignores them. */
unsigned int frame_optional_three_effect_begin(struct FrameNeedEffectState *,struct FrameObject *,unsigned int);
void frame_optional_three_effect_tick(struct FrameObject *);
unsigned int frame_optional_three_effect_select(struct FrameNeedEffectState *, unsigned char *);
/* EC unused formal roles remain inferred until its generic consumer is identified. */
unsigned int frame_optional_three_effect_prepare(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_optional_three_effect_attachment_status(struct FrameNeedEffectState *, struct FrameObject *);
void frame_optional_three_effect_state_tick(struct FrameNeedEffectState *);
/* Adjacent unrooted leaf; row41's field +24 is null. No query role is established. */
unsigned int frame_optional_three_effect_default_value(void);
/* Separate adjacent predicate; no installed callback or incoming role is established. */
unsigned int frame_check_optional_three_effect_count(struct FrameNeedEffectState *, struct FrameObject *);
#endif
