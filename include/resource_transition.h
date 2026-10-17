#ifndef RESOURCE_TRANSITION_H
#define RESOURCE_TRANSITION_H

struct FrameObject;

struct FrameObject *frame_allocate_scene_object(void);
struct FrameObject *resource_create_transition(unsigned int);
void transition_object_tick_windows(struct FrameObject *);
void resource_transition_delay_tick(struct FrameObject *);
/* The observed table prefix contains window, delay and alpha callbacks. */
extern void (*g_resource_transition_steps[])(struct FrameObject *);

#endif
