#ifndef FRAME_NEED_EFFECT_AVERAGE_H
#define FRAME_NEED_EFFECT_AVERAGE_H

#include "display_need_effect_lifecycle.h"

/* A strided callback view rooted at definition byte +0x18; each record is 36 bytes. */
struct FrameNeedEffectAverageCallbackEntry {
    unsigned char (*query)(struct FrameNeedEffectState *);
    unsigned char unknown_04[32];
};
extern const struct FrameNeedEffectAverageCallbackEntry
    g_frame_need_effect_average_callbacks[];
struct FrameActorNeedState;
extern unsigned char g_frame_actor_local_need_state[];
unsigned char frame_actor_need_value(struct FrameActorNeedState *, unsigned int);
void frame_adjust_actor_needs(struct FrameActorNeedState *, unsigned int,
                              unsigned char);
int display_bios_div(int, int);
unsigned char frame_need_effect_average(unsigned char *);
void frame_update_need7_from_effects(void);

#endif
