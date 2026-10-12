#ifndef FRAME_INDICATOR_H
#define FRAME_INDICATOR_H

#include "frame_actor_runtime.h"
struct FrameIndicatorObject {
 FrameU8 unknown_00[12];
 FrameU32 flags;
 FrameU8 unknown_10[60];
 FrameU8 indicator_id, state, unknown_4e[22];
 FrameU16 duration;
 FrameU8 timed, unknown_67[33];
 void (*on_step)(struct FrameObject *);
 void (*on_remove)(struct FrameObject *);
 FrameU32 unknown_90;
 struct FrameObject *actor;
 void (*before_step)(struct FrameObject *);
 FrameU8 unknown_9c[52];
 struct FrameOam oam;
};
extern struct FrameVariantResource g_frame_indicator_resources[];
struct FramePaletteSlot { FrameU8 unknown_00[6], users, unknown_07; };
extern struct FramePaletteSlot g_frame_palette_slots[];
void frame_acquire_palette_slot(struct FrameObject *, int);
void frame_indicator_tick(struct FrameObject *);

#endif
