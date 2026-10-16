#ifndef FRAME_NEED_EFFECT_SPECIAL_H
#define FRAME_NEED_EFFECT_SPECIAL_H
#include "frame_need_effect.h"
#include "input.h"
#include "view_configuration.h"

/* Partial callback work view; these fields follow accesses in this path. */
struct FrameNeedEffectSpecialWork {
    unsigned char unknown_00[0x18];
    struct FramePoint position;
    unsigned char unknown_20[8];
    struct FramePoint velocity;
    unsigned char unknown_30[0x1d], state, variant_state, unknown_4f[15];
    unsigned short countdown;
    unsigned char unknown_60[0x30];
    struct FrameObject *companion;
};
struct FrameNeedEffectPlayerSlot {
    struct FrameObject *object;
    unsigned char unknown_04[8];
};
extern struct FrameVariantResource g_need_effect_special_animation_first;
extern struct FrameVariantResource g_need_effect_special_animation_second;
void frame_commit_need_effect(struct FrameObject *, unsigned int);
void frame_set_actor_direction(struct FrameObject *, unsigned char);
unsigned char frame_object_has_flags(struct FrameObject *, unsigned int);
void frame_disable_object_flags(struct FrameObject *, unsigned int);
void scene_submit_default_request(unsigned int);
void frame_acquire_palette_slot(struct FrameObject *, int);
struct FrameObject *frame_create_need_effect_companion(struct FramePoint);
#endif
