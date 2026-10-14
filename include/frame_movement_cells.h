#ifndef FRAME_MOVEMENT_CELLS_H
#define FRAME_MOVEMENT_CELLS_H

#include "frame_movement.h"

/* The point and its signed high halfwords share the observed eight bytes. */
union FrameMovementCellPoint {
    struct FramePoint point;
    short half[4];
};

#endif
