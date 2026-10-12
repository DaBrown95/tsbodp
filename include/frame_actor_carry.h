#ifndef FRAME_ACTOR_CARRY_H
#define FRAME_ACTOR_CARRY_H
struct FrameActorCarryWork {
 unsigned char unknown00[0x58]; int timer; unsigned char unknown5c[12];
 /* Attachment-adjusted integer coordinates and one-shot alignment byte. */
 unsigned short x,y; unsigned char align,unknown6d[3];
};
#include "resource_view_effects.h"
unsigned char frame_read_attachment(struct FrameObject *,unsigned char,struct FramePoint *);
#include "frame_actor_effect.h"
void frame_actor_state_42(struct FrameObject *);
#endif
