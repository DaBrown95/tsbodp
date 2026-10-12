#ifndef FRAME_CONSTRUCTOR_H
#define FRAME_CONSTRUCTOR_H

#include "frame_actor_runtime.h"
#include "view_math.h"

/* A pair-per-direction view of the same extended velocity table. */
extern struct FramePoint g_frame_direction_16[];
void frame_enable_parts(struct FrameObject *);
void frame_set_part_order(struct FrameObject *, FrameU8, FrameU8);
void frame_set_position(struct FrameObject *, int, int);
void frame_refresh_velocity(struct FrameObject *);
void frame_set_directional_acceleration(struct FrameObject *, unsigned int, int);

#endif
