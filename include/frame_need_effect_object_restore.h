#ifndef FRAME_NEED_EFFECT_OBJECT_RESTORE_H
#define FRAME_NEED_EFFECT_OBJECT_RESTORE_H

#include "frame_need_effect.h"
#include "frame_actor_scene.h"

/* Read-only prefix used by the observed 125/126/139 F8 path. The union keeps
 * the signed pixel halves and full fixed-point words in the same storage. */
struct FrameNeedEffectRestoreObject {
    unsigned char unknown_00[0x0c];
    unsigned int flags;
    unsigned char unknown_10[2], direction, unknown_13[5];
    union FramePointStorage position;
};

/* These signatures repeat the existing canonical provider declarations. */
struct FrameSceneSavedEffect;
struct FrameObject *frame_create_option_object(unsigned int, unsigned char,
                                              unsigned char, short, short);
struct FrameSceneSavedEffect *frame_spawn_saved_scene_effect(int, int);
void transition_object_set_state(void *, unsigned char);

/* Installed by the three observed rows; wider writable populations are open. */
void frame_restore_need_effect_object(struct FrameNeedEffectState *);

#endif
