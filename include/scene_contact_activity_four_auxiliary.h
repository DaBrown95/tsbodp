#ifndef SCENE_CONTACT_ACTIVITY_FOUR_AUXILIARY_H
#define SCENE_CONTACT_ACTIVITY_FOUR_AUXILIARY_H

#include "scene_contact_activity_four_objects.h"
#include "input.h"

/* Whole-object-rooted 212-byte prefix within the observed 320-byte allocation.
 * The nested byte at +D3 has its own alignment-one representation; this view
 * does not establish complete storage or original declarations. */
struct __attribute__((packed, aligned(1))) SceneContactAuxiliaryFlagByte {
    unsigned char unknown_0:4;
    signed char flag4:1;
    unsigned char flag5:1, unknown_6:2;
};
struct SceneContactAuxiliaryFlagPrefix {
    unsigned char unknown00[211];
    struct SceneContactAuxiliaryFlagByte flags;
};

void scene_contact_activity_four_step_auxiliary_object(struct FrameObject *);

#endif
