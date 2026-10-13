#ifndef FRAME_OPTION_OBJECT_H
#define FRAME_OPTION_OBJECT_H

#include "frame_actor_animation.h"
#include "frame_actor_scene.h"
#include "input.h"
#include "resource_object_payload.h"
#include "transition_object.h"
struct FrameOptionObject {
 unsigned char unknown00[8]; unsigned short id,subtype; unsigned int flags;
 unsigned char owner_id,owner_slot,direction,option; int speed;
 struct FramePoint position,next_position,velocity,acceleration,destination;
 unsigned char unknown40[12]; unsigned char kind,state,variant,pending;
 unsigned char unknown50[8]; int timer;
 unsigned char unknown5c[2]; unsigned short need_timer;
 unsigned char unknown60[4]; struct FrameObject *target;
 unsigned short time0,time1,time2,time3;
 unsigned char unknown70[0x84-0x70],field84,unknown85[3];
 void (*on_step)(struct FrameObject *);
 unsigned char unknown8c[0xc8-0x8c];
 void (*on_primary)(struct FrameObject *,struct FrameObject *);
 void (*on_secondary)(struct FrameObject *,struct FrameObject *);
 struct FrameOam oam;
};
struct FrameOptionAnimations { struct FrameVariantResource *variants[3]; };
struct FrameOptionDefinition {
 void (*configure)(struct FrameObject *);
 void (*on_primary)(struct FrameObject *,struct FrameObject *);
 void (*on_secondary)(struct FrameObject *,struct FrameObject *);
 int speed;
};
struct FrameOptionPayload { unsigned char unknown00[4]; short x,y; unsigned char kind,direction,option; };
/* Only its address is consumed by the signed-parameter reader. */
struct FrameOptionNeedParameters;
extern struct FrameOptionNeedParameters g_frame_option_need_parameters;
extern struct FrameOptionAnimations g_frame_option_animation_sets[];
extern struct FrameOptionDefinition g_frame_option_definitions[];
extern const void *g_frame_option_palettes[];
struct FrameObject *frame_allocate_object(int);
void frame_set_position(struct FrameObject *,int,int);
void frame_update_actor_state(struct FrameObject *);
void frame_set_subtype_object_palette(struct FrameObject *,const void *const *);
void frame_acquire_palette_slot(struct FrameObject *,int);
int frame_read_signed_parameter(const void *,unsigned int);
unsigned int condition_group_active(unsigned char,unsigned char);
unsigned int condition_is_complete(unsigned char,unsigned char,unsigned char);
void frame_option_tick(struct FrameObject *);
void frame_option_interact(struct FrameObject *,struct FrameObject *);
struct FrameObject *frame_create_option_object(unsigned int,unsigned char,unsigned char,short,short);
struct ConditionActorEntries;
struct FrameOptionWorld { unsigned char unknown00[0xf0]; struct ConditionActorEntries *entries; };
struct FrameOptionPlayerSlot { struct FrameObject *object; unsigned char unknown04[8]; };
struct FrameOptionPlayerContext { struct FrameOptionPlayerSlot players[4]; unsigned char count,local_player; };
struct FrameOptionRequest { unsigned char unknown00,reset1,reset2,unknown03,active; };
struct FrameOptionChoiceState { unsigned char unknown00[12]; int result; };
struct FrameOptionUiRecord { unsigned int flags; unsigned char unknown04[52]; };
struct FrameOptionUiRoot { unsigned char unknown00[4]; struct FrameOptionUiRecord rows[4]; };
extern struct FrameOptionUiRoot g_scene_mode_flags;
void frame_refresh_velocity(struct FrameObject *);
void frame_stop_motion(struct FrameObject *);
void frame_run_actor_state(struct FrameObject *);
void resource_set_triple(unsigned int,unsigned int,unsigned int);
unsigned char frame_scene_effect_facing_available(struct FrameObject *,struct FrameObject *);
void frame_need_effect_stop_at_position(struct FrameObject *);
void frame_disable_object_flags(struct FrameObject *,unsigned int);
void frame_enable_object_flags(struct FrameObject *,unsigned int);
void scene_submit_default_request(unsigned int);
int actor_entry_has_space(struct ConditionActorEntries *);
unsigned int actor_entry_add(struct ConditionActorEntries *,unsigned int,unsigned char,unsigned char);
void frame_option_configure(struct FrameObject *);
void frame_option_action_step(struct FrameObject *);
struct FrameOptionInputSlot { unsigned char unknown00[0x13], input_slot; };
void frame_option_contact_interact(struct FrameObject *,struct FrameObject *);
void frame_option_restricted_interact(struct FrameObject *,struct FrameObject *);
void frame_option_initialize(struct FrameObject *);
struct FrameObject *frame_create_option_resource(unsigned char,unsigned char);

#endif
