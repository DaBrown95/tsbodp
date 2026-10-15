#ifndef FRAME_NEED_EFFECT_ACTOR_HEADER_H
#define FRAME_NEED_EFFECT_ACTOR_HEADER_H

struct FrameNeedEffectState;
struct FrameObject;
/* Observed E4 check; actor halfword +0x0A has no established wider meaning. */
unsigned int frame_need_effect_check_actor_header(struct FrameNeedEffectState *,
                                                 struct FrameObject *);

#endif
