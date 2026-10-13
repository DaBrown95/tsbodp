#ifndef FRAME_GROUP_SELECTOR_H
#define FRAME_GROUP_SELECTOR_H

#include "frame_actor_animation.h"
#include "resource_object_payload.h"
#include "input.h"
#include "transition_object.h"
struct FrameGroupSelectorPayload {
 unsigned int id; short x,y;
 unsigned char subtype,cue,available,object_group,program_group;
};
struct FrameGroupSelectorObject {
 unsigned char unknown00[8]; unsigned short id,subtype; unsigned int flags;
 unsigned char unknown10[0x4d-0x10]; unsigned char state;
 unsigned char unknown4e[0x68-0x4e];
 unsigned char object_group,program_group,cue,available;
 unsigned char unknown6c[0x88-0x6c];
 void (*on_step)(struct FrameObject *);
 unsigned char unknown8c[0xc8-0x8c];
 void (*on_primary)(struct FrameObject *,struct FrameObject *);
 void (*on_secondary)(struct FrameObject *,struct FrameObject *);
 struct FrameOam oam;
};
extern int g_frame_group_selector_palettes[];
extern struct FrameVariantResource g_frame_group_selector_animations[];
struct FrameObject *frame_allocate_scene_object(void);
void frame_set_position(struct FrameObject *,int,int);
void frame_acquire_palette_slot(struct FrameObject *,int);
void frame_set_animation_frame(struct FrameTickObject *,unsigned char);
void frame_run_actor_state(struct FrameObject *);
void resource_activate_groups(unsigned char,unsigned char);
void frame_group_selector_step(struct FrameObject *);
void frame_group_selector_interact(struct FrameObject *,struct FrameObject *);
struct FrameObject *frame_create_group_selector(unsigned char,unsigned char);

#endif
