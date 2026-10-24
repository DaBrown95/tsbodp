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
/* Forty-byte definitions have eight entries per group and sixteen stored
 * halfword offsets. The serialized frame count is not validated here. */
struct FrameTransientDefinition {
 const void *resource;
 unsigned short frames[16];
 unsigned short index;
 unsigned char unknown26,frame_count;
};
extern unsigned char g_frame_transient_free_pool[];
extern struct FrameObjectList g_frame_transient_active_list;
extern unsigned short g_frame_transient_count,g_frame_transient_maximum;
extern struct FrameTransientDefinition g_frame_transient_definitions[][8];
struct FrameTransientEffect *frame_create_transient_effect(unsigned char,unsigned char,unsigned char);
void frame_destroy_transient_effect(struct FrameTransientEffect *);
void frame_release_transient_definition_tiles(unsigned char,unsigned char);
void frame_release_scene_transient_tiles(void);
void frame_clear_scene_effects(void);
void frame_spawn_counter_effect(struct FrameObject *,signed char);
void frame_clear_transient_effects(void);
void frame_reset_effect_lists_unrooted_30f70(void);
void frame_step_transient_effects(void);
void frame_step_owner_transient_effects(struct FrameObject *);
void frame_step_transient_effect(struct FrameTransientEffect *);
void frame_emit_transient_render_effect(struct FrameTransientEffect *);
#endif
