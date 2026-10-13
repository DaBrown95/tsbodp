#ifndef FRAME_MAP_ANIMATION_H
#define FRAME_MAP_ANIMATION_H

#include "frame_map_scene.h"
#include "resource_object_payload.h"
#include "transition_object.h"
struct FrameMapAnimationPosition { unsigned short fraction; short integer; };
struct FrameMapAnimationObject {
 unsigned char unknown00[8]; unsigned short id,subtype; unsigned int flags;
 unsigned char owner_group,owner_slot,unknown12[6];
 struct FrameMapAnimationPosition x,y;
 unsigned char unknown20[0x4c-0x20]; unsigned char kind,state,variant,pending;
 unsigned char unknown50[0x64-0x50];
 unsigned char reverse,one_shot,enabled,started,latched,signal;
 unsigned char step,period,current,first,last,span,timer,polarity,map,width,height,sound;
 unsigned char unknown76[0x88-0x76]; void (*on_step)(struct FrameObject *);
};
struct FrameMapAnimationPayload {
 unsigned int id; short x,y;
 unsigned char kind,reverse,map,first,frames,period,one_shot,polarity,group,slot,sound;
};
struct FrameMapAnimationSimplePayload {
 unsigned int id; short x,y;
 unsigned char map,first,frames,width,height,period,one_shot,repeat;
};
struct FrameMapAnimationDefinition { unsigned char unknown00[4],width,height,step,unknown07; };
extern const struct FrameMapAnimationDefinition g_frame_map_animation_definitions[];
extern unsigned int g_frame_map_animation_sample;
struct FrameObject *frame_allocate_object(int);
struct FrameObject *frame_allocate_scene_object(void);
void frame_set_position(struct FrameObject *,int,int);
void resource_activate_groups(unsigned char,unsigned char);
unsigned char audio_game_sample_active(unsigned int);
void frame_run_actor_state(struct FrameObject *);
void frame_map_animation_tick(struct FrameObject *);
void frame_map_animation_simple_tick(struct FrameObject *);
void frame_map_animation_write_rectangle(struct FrameObject *);
void frame_write_extra_map_cell(unsigned short,unsigned short,unsigned short);
struct FrameObject *frame_create_map_animation(unsigned char,unsigned char);
struct FrameObject *frame_create_map_animation_simple(unsigned char,unsigned char);

#endif
