#ifndef SCENE_CONTACT_ACTIVITY_FOUR_PRIMARY_H
#define SCENE_CONTACT_ACTIVITY_FOUR_PRIMARY_H

#include "scene_contact_activity_four_objects.h"
#include "input.h"

/* Alternate target representation of the same control pointer at +58.
 * The 92-byte prefix stays within the observed 420-byte state allocation;
 * it does not change the existing pointer-array view or imply full storage. */
union SceneContactActivityFourControlAddress {
    unsigned int address;
    struct FrameObject *pointer;
};
struct SceneContactActivityFourPrimaryState {
    unsigned char unknown00[0x58];
    union SceneContactActivityFourControlAddress control;
};

void scene_contact_activity_four_step_primary_object(struct FrameObject *);

#endif
