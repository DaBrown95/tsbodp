#ifndef FRAME_POSITION_CYCLE_LIFECYCLE_H
#define FRAME_POSITION_CYCLE_LIFECYCLE_H

#include "frame_position_cycle_jobs.h"

/* Shared initializer and F8 tick of observed rows 59..62 and 80..82.
 * The initializer's result is ignored; its unused historical formal and return
 * declarations are not uniquely proved. Wider callback populations remain open. */
unsigned int frame_initialize_position_cycle_jobs(struct FrameNeedEffectState *);
void frame_tick_position_cycle_jobs(struct FrameNeedEffectState *);

#endif
