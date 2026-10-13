#ifndef FRAME_NEED_EFFECT_OPTIONAL_H
#define FRAME_NEED_EFFECT_OPTIONAL_H

#include "frame_need_effect.h"
#include "frame_random.h"
#include "audio_game.h"

/* Four-byte ROM row; the increment is signed, while the chance is a byte. */
struct FrameNeedOptionalThreshold {
    short increment;
    unsigned char threshold, unknown_03;
};
extern const struct FrameNeedOptionalThreshold g_frame_need_optional_thresholds[];

/* Selector-specific overlapping object view; the slot's broader role is unknown. */
struct FrameNeedOptionalObjectView {
    unsigned char unknown_00[0x90];
    struct FrameObject *object_slot_90;
};

unsigned int frame_need_effect_try_optional(struct FrameNeedEffectState *);
void frame_need_effect_play_optional_cue(struct FrameNeedEffectState *);

#endif
