#ifndef FRAME_ACTOR_SPEED_EXIT_H
#define FRAME_ACTOR_SPEED_EXIT_H
#include "frame_actor_scene.h"
#include "frame_actor_speed_control.h"
/* Only the exit callback's observed fields are named in these views. */
struct FrameActorExitPalette { unsigned char unknown00[0x42d], palette; };
struct FrameSpeedExitSceneResult { unsigned char unknown00[12]; int result; };
struct CollisionObject;
struct FrameSpeedExitCallbacks {
 unsigned char unknown00[0xc8];
 unsigned int scratch;
 void (*on_interact)(struct CollisionObject *, struct CollisionObject *);
};
extern unsigned char g_frame_actor_exit_variants[];
extern struct FrameVariantResource g_frame_actor_exit_resources[];
extern unsigned short g_actor_exit_scene_defaults[2];
void frame_speed_exit_tick(struct FrameObject *);
void frame_speed_exit_interact(struct CollisionObject *, struct CollisionObject *);
void frame_speed_exit_transition(struct FrameObject *);
void frame_acquire_palette_slot(struct FrameObject *, int);
void frame_enable_object_flags(struct FrameObject *, unsigned int);
#endif
