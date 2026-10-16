#ifndef FRAME_NEED_EFFECT_REGISTRATION_H
#define FRAME_NEED_EFFECT_REGISTRATION_H

#include "frame_need_effect_placement.h"
#include "frame_actor_target_cells.h"

/* Registration clears 48 candidate bytes and 40 target bytes, then publishes
 * two points. This bounded view does not establish the complete allocation or
 * a capacity invariant for every serialized action pattern. */
struct FrameNeedEffectSpatialWork {
 unsigned char unknown00[0x74];
 struct FrameNeedEffectCell candidates[12],targets[10];
 struct FramePoint far_bounds,near_bounds;
};
/* Object +0xA4 is the canonical spatial.bounds.upper point. */
unsigned char frame_grid_cell_extents(void *, const int *,
                                     struct FramePoint *, struct FramePoint *);

#endif
