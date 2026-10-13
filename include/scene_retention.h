#ifndef SCENE_RETENTION_H
#define SCENE_RETENTION_H

struct FrameObject;
struct FrameObjectList;
extern struct FrameObjectList g_frame_retained_primary_list;
void frame_retain_primary_objects(void), frame_restore_primary_objects(void);
void frame_enable_primary_object_flags(unsigned int), frame_disable_primary_object_flags(unsigned int);
void background_animation_reset(void), scene_stop_actor_speed_cue(void);
void frame_enable_object_flags(struct FrameObject *, unsigned int);
void background_animation_stop(void), background_animation_clear(void);
void background_animation_force_reload(void);
#endif
