#ifndef FRAME_SCENE_OBJECT_H
#define FRAME_SCENE_OBJECT_H
#include "frame_actor_runtime.h"
#include "frame_actor_scene.h"
struct FrameObject *frame_allocate_scene_object(void);
void frame_scene_object_tick(struct FrameObject *);
struct FrameScenePosition { short x0, y0, x1, y1; };
extern struct FrameScenePosition g_frame_scene_positions[];
extern struct FrameVariantResource g_frame_scene_resources[];
extern unsigned char g_frame_scene_special_palette[], g_frame_scene_commands_110[], g_frame_scene_commands_111[];
extern unsigned char g_frame_object_pool[];
#include "frame_pool.h"
#endif
