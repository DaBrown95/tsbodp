#ifndef FRAME_SCENE_PLAYER_H
#define FRAME_SCENE_PLAYER_H

#include "frame_actor_runtime.h"
struct FrameScenePlayerMode {unsigned char unknown00[0x42e],mode;};
extern struct FrameScenePlayerMode g_frame_scene_player_mode;
extern signed char g_frame_scene_double_direction_variants[];
extern unsigned char g_scene_mode_bytes[];
struct FrameScenePlayerSpawnResource {short x,y;unsigned char unknown04[2],direction;};
struct FrameScenePlayerSpawnResource *frame_scene_player_spawn_resource(unsigned char,unsigned char);
struct FrameScenePlayerFallback {unsigned char unknown00[7],direction;short x,y;};
extern struct FrameScenePlayerFallback g_frame_scene_player_fallback;
struct FrameScenePlayerGroup {unsigned char mode;};
extern struct FrameScenePlayerGroup g_frame_scene_player_group;
struct FrameScenePlayerSlot {struct FrameObject *object;unsigned char unknown04[8];};
extern struct FrameScenePlayerSlot g_frame_scene_player_slots[];
extern unsigned char *g_frame_actor_commands_kind1[],*g_frame_scene_player_commands_kind2[];
void frame_scene_initialize_player_state(struct FrameObject *,unsigned char);
void frame_acquire_palette_slot(struct FrameObject *,int);
void frame_enable_animation_part(struct FrameObject *,unsigned char);
void frame_scene_player_collision(struct FrameObject *,struct FrameObject *);
extern unsigned char g_frame_actor_local_need_state[];
struct FrameScenePlayerCollision {unsigned char unknown00[0xc8];void (*collision)(struct FrameObject *,struct FrameObject *);};

/* Shared allocations return a 320-byte object; this wrapper assigns its id. */
struct FrameObject *frame_allocate_scene_object(void);
struct FrameObject *frame_scene_player_actor(unsigned char);
struct FrameObject *frame_create_scene_primary_actor(void);
extern struct FrameVariantResource g_frame_scene_primary_animation;
void frame_scene_primary_tick(struct FrameObject *);
struct FrameSceneSpawnObject {
 struct FrameSceneSpawnObject *next,*previous;
 unsigned short id,subtype;
 unsigned int flags;
 unsigned char owner_id,owner_slot,direction,unknown13[5];
 struct FramePoint position;
};
struct FrameSceneSpawnList {struct FrameSceneSpawnObject *first,*last;};
extern struct FrameSceneSpawnList g_frame_scene_spawn_list;
unsigned char frame_scene_read_spawn(unsigned char,unsigned char *,int *,int *);

#endif
