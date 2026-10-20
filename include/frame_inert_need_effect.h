#ifndef FRAME_INERT_NEED_EFFECT_H
#define FRAME_INERT_NEED_EFFECT_H
#include "frame_need_effect.h"
/* Installed by observed rows8/105/116. Consumed arguments and effects are
 * supported; extra historical unused formals and generic EC/FC delivery remain open. */
unsigned int frame_inert_need_effect_initialize(struct FrameNeedEffectState *);
unsigned int frame_inert_need_effect_select(struct FrameNeedEffectState *, unsigned char *);
unsigned int frame_inert_need_effect_prepare(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_inert_need_effect_begin(struct FrameNeedEffectState *, struct FrameObject *, unsigned int);
unsigned int frame_inert_need_effect_dispatch(struct FrameNeedEffectState *, struct FrameObject *);
void frame_inert_need_effect_tick(struct FrameNeedEffectState *);
unsigned char frame_inert_need_effect_value(struct FrameNeedEffectState *);
/* No input is consumed; no incoming root is established for this separate leaf. */
unsigned int frame_unrooted_need_effect_one_46594(void);
unsigned int frame_unrooted_need_effect_hundred_4658c(void);
#endif
