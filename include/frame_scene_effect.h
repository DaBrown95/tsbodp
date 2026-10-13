#ifndef FRAME_SCENE_EFFECT_H
#define FRAME_SCENE_EFFECT_H

/* Bounded work view. Counter and signed comparisons are observed; names remain provisional. */
#include "frame_scene_player.h"
#include "frame_actor_state.h"
#include "view_math.h"
#include "audio_game.h"
#include "input.h"
struct FrameSceneEffectWork {
 struct FrameObject *next,*previous;
 unsigned short id,subtype;
 unsigned int flags;
 unsigned char owner_id,owner_slot,direction,unknown13;
 int speed;
 struct FramePoint position,next_position,velocity,acceleration,destination;
 unsigned char unknown40[12],kind,state,variant_state,pending_updates,unknown50,default_state,unknown52[2];
 unsigned int route_status;
 int timer;
 unsigned char unknown5c[4];
 void *actor_state;
 struct FrameObject *owner,*partner;
 int value;
};
struct FrameSceneNeedFields {unsigned char unknown00[0x83],linked;};
struct FrameSceneNeedRender {unsigned char unknown00[0xd5],attribute1_high;};
struct FrameObject *frame_spawn_need_effect(int,int,int,int,int);
unsigned char frame_configure_need_effect(struct FrameObject *,int,int,int);
void frame_commit_need_effect(struct FrameObject *,unsigned int);
void frame_scene_effect_configure(struct FrameObject *,unsigned char);
void frame_scene_effect_walk_972c(struct FrameObject *);
void frame_scene_effect_replenish_9710(struct FrameObject *);
void frame_scene_effect_follow_9758(struct FrameObject *);
struct FrameActorNeedState;
void frame_adjust_actor_needs(struct FrameActorNeedState *,unsigned int,unsigned char);
extern void *g_frame_registration;

#include "frame_actor_scene.h"
#include "resource_condition_entries.h"
struct SceneModeFlags;
struct FrameSceneEffectRequest {unsigned char unknown00,reset1,reset2,unknown03,active;};
struct FrameSceneEffectMenuSelection {unsigned char unknown00[12];int selection;};
struct FrameSceneEffectActorEntryView {unsigned char unknown00[0xf0];struct ConditionActorEntries *entries;};
struct FrameSceneEffectUiRecord {unsigned int changed;unsigned char unknown04[52];};
struct FrameSceneEffectUi {unsigned char unknown00[4];struct FrameSceneEffectUiRecord views[4];};
extern struct SceneModeFlags g_scene_mode_flags;
extern unsigned short g_frame_scene_effect_menu_labels[],g_frame_scene_effect_menu_actions[];
unsigned int actor_entry_add(struct ConditionActorEntries *,unsigned int,unsigned char,unsigned char);
void frame_disable_object_flags(struct FrameObject *,unsigned int);
void frame_enable_object_flags(struct FrameObject *,unsigned int);

#include "frame_actor_speed.h"

extern int g_frame_scene_effect_speeds[];
void resource_scene_event(unsigned int);
unsigned char frame_scene_effect_facing_available(struct FrameObject *,struct FrameObject *);
void frame_scene_effect_state_8e14(struct FrameObject *);
void frame_scene_effect_state_91f4(struct FrameObject *);
void frame_scene_effect_update_950c(struct FrameObject *);
#endif
