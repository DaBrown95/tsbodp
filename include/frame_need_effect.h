#ifndef FRAME_NEED_EFFECT_H
#define FRAME_NEED_EFFECT_H

#include "frame_actor_runtime.h"
struct FrameNeedEffectState {
 FrameU8 unknown_00[8];
 FrameU32 kind;
 FrameU8 unknown_0c[72];
 struct FrameObject *object;
 FrameU8 unknown_58[7], mode;
 FrameU8 unknown_60[2], enabled, unknown_63[13];
 FrameU16 parameter;
 FrameU8 optional;
};
struct FrameNeedEffectObject {
 struct FrameObject *next,*previous;
 FrameU16 id,subtype;
 FrameU32 flags;
 FrameU8 unknown_10[2],direction,unknown_13[5];
 struct FramePoint position,next_position;
 FrameU8 unknown_28[36];
 FrameU8 kind,state,unknown_4e[22];
 struct FrameNeedEffectState *effect_state;
 FrameU32 effect_flags;
 FrameU8 effect_values[14], effect_choices[7];
 FrameU8 phase,mode,linked,unknown_84[4];
 void (*on_step)(struct FrameObject *);
 void (*on_remove)(struct FrameObject *);
 FrameU8 unknown_90[8];
 void (*before_step)(struct FrameObject *);
 FrameU8 unknown_9c[52];
 struct FrameOam oam;
 FrameU8 unknown_d8[41],sharing_flags,shared_group;
 signed char requested_animation;
 struct FrameAnimationPart parts[4];
};
struct FrameNeedEffectDefinition { void *callback; FrameU8 unknown_04[32]; };
extern struct FrameNeedEffectDefinition g_frame_need_effect_definitions[];
void frame_enable_object_flags(struct FrameObject *, FrameU32);
void frame_fill_bytes(void *, int, int);
FrameU8 frame_need_effect_world_option(int,int);
void frame_need_effect_special_tick(struct FrameObject *);
void frame_need_effect_tick(struct FrameObject *);
void frame_need_effect_remove(struct FrameObject *);
void frame_need_effect_before_step(struct FrameObject *);
struct FrameNeedEffectState *frame_allocate_need_effect_state(FrameU32);
void frame_need_effect_initialize(struct FrameNeedEffectState *,void *);
void frame_update_need_effect(struct FrameObject *);

struct FrameObject *frame_spawn_need_effect(int, int, int, int, int);

#endif
