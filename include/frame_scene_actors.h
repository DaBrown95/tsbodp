#ifndef FRAME_SCENE_ACTORS_H
#define FRAME_SCENE_ACTORS_H

#include "frame_scene_player.h"
#include "frame_actor_finish.h"
#include "scene.h"
#include "input.h"
struct TransitionViewObject;
void transition_reset_view(unsigned char);
void transition_set_view_mode(unsigned int,unsigned char);
void transition_configure_view(struct TransitionViewObject *,struct FramePoint,unsigned char);
#include "transition_view_configuration.h"
void resource_spawn_group(unsigned char),resource_execute_group(unsigned char);
extern unsigned short g_resource_group_flags;
void resource_prepare(const unsigned char *);
struct FrameObject *frame_scene_player_actor(unsigned char);
struct ActorEntryContext;
void actor_entry_restore_scene_collection(struct ActorEntryContext *,unsigned int),actor_entry_mark_scene_collection(struct ActorEntryContext *,unsigned int);
struct FrameObject *frame_create_scene_primary_actor(void);
extern struct FrameObject *g_frame_scene_active_actor;
struct FrameObject *frame_create_speed_exit_actor(unsigned char,int,int);
unsigned char frame_scene_read_spawn(unsigned char,unsigned char *,int *,int *);
/* Partial saved scene-entry and selected-actor views; +0x740 is distinct from +0x748. */
struct FrameSceneEntrySnapshot {unsigned char unknown00[0x348];struct FramePoint position;unsigned char world,unknown351,exit_flag;};

void frame_initialize_scene_actors(unsigned int);

#endif
