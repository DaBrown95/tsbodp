#ifndef DISPLAY_CONDITION_MARKER_H
#define DISPLAY_CONDITION_MARKER_H

#include "frame_actor_runtime.h"
#include "resource_object_payload.h"
#include "resource_conditions.h"

/* Accessed payload prefix through byte +0x0D. Alignment does not establish
 * an allocation size, table stride or valid row/column/entry domains. */
struct ConditionMarkerPayload {
    int id;
    short x, y;
    unsigned char row, column, entry, completed, group, slot;
};

/* Partial view of the shared FrameObject storage through byte +0x67. */
struct ConditionMarkerState {
    unsigned char unknown00[0x4D];
    unsigned char state, variant, pending;
    unsigned char unknown50[0x14];
    unsigned char row, column, entry, completed;
};

struct FrameObject *condition_marker_create(unsigned char, unsigned char);
void condition_marker_step(struct FrameObject *);
void frame_enable_object_flags(struct FrameObject *, unsigned int);
void resource_activate_groups(unsigned char, unsigned char);

#endif
