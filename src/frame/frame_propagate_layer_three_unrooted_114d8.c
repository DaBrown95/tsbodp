#include "frame.h"

/* Unrooted two-input body; names and incoming object domains are provisional. */
void frame_propagate_layer_three_unrooted_114d8(struct FrameObject *first,
                                              struct FrameObject *second)
{
    if (first->display_layer == 3 || second->display_layer == 3) {
        if (first->position.y < second->position.y) {
            first->display_layer = 3;
            second->display_layer = 3;
        }
    }
}
