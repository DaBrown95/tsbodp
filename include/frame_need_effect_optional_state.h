#ifndef FRAME_NEED_EFFECT_OPTIONAL_STATE_H
#define FRAME_NEED_EFFECT_OPTIONAL_STATE_H

#include "frame_need_effect_optional.h"
#include "display_actor_interaction.h"
#include "frame_actor_effect.h"

/* The mode-three entry calls only this slot of another need-effect state. */
struct FrameNeedOptionalApplyCallbacks {
    unsigned char unknown_00[0xf0];
    void (*apply)(struct FrameNeedEffectState *, unsigned int, unsigned int);
};
extern unsigned char g_frame_actor_social_probe[];
extern struct FrameObject *g_need_effect_player;
int frame_read_signed_parameter(const void *, unsigned int);
unsigned char frame_find_objects(unsigned char, unsigned char, struct FrameObject **,
                                unsigned char);

void frame_need_effect_accumulate_optional(struct FrameNeedEffectState *);
unsigned char frame_need_effect_try_actor_effect(struct FrameNeedEffectState *,
                                                struct FrameObject *);
void frame_need_effect_set_optional_one(struct FrameNeedEffectState *, unsigned short);
void frame_need_effect_set_optional_two(struct FrameNeedEffectState *, unsigned short);
void frame_need_effect_begin_optional_three(struct FrameNeedEffectState *);

#endif
