#ifndef FRAME_DAILY_FLAG_CREATION_H
#define FRAME_DAILY_FLAG_CREATION_H

#include "frame_daily_flags.h"
#include "resource_object_payload.h"
#include "input.h"

/* Read-only serialized payload prefix observed by factory slot 16. */
struct FrameDailyFlagPayload {
    unsigned int id;
    short x,
        y;
    unsigned char subtype,
        index;
};

/* Object write view through +D5; pool allocation is established elsewhere.
 * The +C8 callback consumes an owner in R1 in this selector path.
 * The broader actor role still has a provisional one-argument declaration. */
struct FrameDailyFlagSpawnObject {
    unsigned char unknown00[8];
    unsigned short id,
        subtype;
    unsigned int flags;
    unsigned char unknown10[0x4d - 0x10];
    unsigned char state,
        variant_state,
        unknown4f[9];
    int timer;
    unsigned char unknown5c[8];
    struct FrameObject *owner;
    unsigned char index;
    unsigned char unknown69[0x88 - 0x69];
    void (*on_step)(struct FrameObject *);
    unsigned char unknown8c[0xc8 - 0x8c];
    void (*on_interact)(struct FrameObject *, struct FrameObject *);
    unsigned char unknowncc[9],
        display_byte;
};

extern const unsigned char g_frame_daily_flag_chances[];
extern struct FrameVariantResource g_frame_daily_flag_animations[];
extern int g_frame_daily_flag_palettes[];
struct FrameObject *frame_allocate_scene_object(void);
struct FrameObject *frame_create_daily_flag_object(unsigned char, unsigned char);
unsigned int frame_test_daily_pending_flag(unsigned int);
void frame_mark_daily_flag(unsigned int);
void frame_mark_daily_pending_flag(unsigned int);
void frame_daily_flag_interact(struct FrameObject *, struct FrameObject *);
void frame_acquire_palette_slot(struct FrameObject *, int);

#endif
