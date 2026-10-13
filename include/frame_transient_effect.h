#ifndef FRAME_TRANSIENT_EFFECT_H
#define FRAME_TRANSIENT_EFFECT_H
#include "frame_pool.h"
/* A separate 72-byte object family; field roles follow the effect producers. */
struct FrameTransientEffect {
 struct FrameTransientEffect *next,*previous; struct FrameObject *owner; const void *resource;
 unsigned char unknown10[8]; struct FramePoint position; int rate; const void *frames;
 unsigned short width,height; unsigned char kind,unknown2d[3];unsigned int flags;
 unsigned short unknown34,unknown36,index;unsigned char phase,direction,enabled,unknown3d;
 unsigned short countdown;unsigned char offset_x,offset_y,unknown42,unknown43,mode,unknown45[3];
};
/* Definitions have a 40-byte stride, with eight entries per group. */
struct FrameTransientDefinition {const void *resource;unsigned char frames[32];unsigned short index;unsigned char unknown26[2];};
extern unsigned char g_frame_transient_free_pool[];
extern struct FrameObjectList g_frame_transient_active_list;
extern unsigned short g_frame_transient_count,g_frame_transient_maximum;
extern struct FrameTransientDefinition g_frame_transient_definitions[][8];
struct FrameTransientEffect *frame_create_transient_effect(unsigned char,unsigned char,unsigned char);
void frame_destroy_transient_effect(struct FrameTransientEffect *);
void frame_spawn_counter_effect(struct FrameObject *,signed char);
#endif
