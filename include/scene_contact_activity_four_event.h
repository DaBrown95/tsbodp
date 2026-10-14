#ifndef SCENE_CONTACT_ACTIVITY_FOUR_EVENT_H
#define SCENE_CONTACT_ACTIVITY_FOUR_EVENT_H

#include "scene_contact_activity_four.h"
#include "view_math.h"

/* Whole-object-rooted prefixes within the observed 320-byte allocation.
 * These views preserve the word at +20 and byte at +76 without extending
 * accesses through the older FrameObject byte-array members. */
struct SceneContactActivityFourEventObject {
    unsigned char unknown00[20];
    int speed;
    unsigned char unknown18[52], slot;
};

struct SceneContactActivityFourEventRow {
    int x, y, speed;
};

/* Same row-four storage, with the callback's observed halfword at +14.
 * The eight pointer slots and nullable-secondary contract remain unchanged. */
struct SceneContactActivityFourEventState {
    struct FrameObject *object;
    unsigned char unknown04[8];
    short score;
    unsigned short current;
    unsigned char unknown10[8];
    struct FrameObject *first[8], *second[8], *control;
    unsigned char selections[8];
};

/* The halfword-backed palette field reproduces this producer's halfword
 * identifier read. Its physical byte mapping is independently checked; the
 * item creator's separate access view retains its existing field types. */
struct SceneContactActivityFourEventFlags {
    unsigned char unknown00[0xd1];
    unsigned char mode:2, contact_mode:2, unknown_d1_4:1;
    unsigned char double_size:1, unknown_d1_6:2;
    unsigned char unknown_d2;
    unsigned char unknown_d3_0:4;
    signed char flag4:1;
    unsigned char flag5:1, unknown_d3_6:2;
    unsigned char unknown_d4;
    unsigned char tile_high:2, layer:2;
    unsigned short palette:4;
};

extern const struct SceneContactActivityFourEventRow
    g_scene_contact_activity_four_event_positions[];

struct FrameObject *scene_contact_activity_four_create_event(void);
void scene_contact_activity_four_step_event(struct FrameObject *);

#endif
