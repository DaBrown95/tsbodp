#ifndef FRAME_NODE_POOL_1DAC4_H
#define FRAME_NODE_POOL_1DAC4_H

#include "frame.h"
#include "frame_pool.h"
#include "heap.h"

/* Only the allocation and two list heads are observed.  The list helpers use
 * active.first; active.last shares storage with the separate free head.
 * The two structures have the same initial sequence of pointer types. */
struct FrameNodePoolState1dac4 {
    void *memory;
    union {
        struct FrameObjectList active;
        struct {
            struct FrameObject *active_head;
            struct FrameObject *free_head;
        } heads;
    } lists;
};

extern struct FrameNodePoolState1dac4 g_frame_node_pool_1dac4;

/* Minimal callable views; incoming roots and unused formals remain unknown. */
void frame_initialize_node_pool_1dac4(void);
void frame_shutdown_node_pool_1daf0(void);
struct FrameObject *frame_allocate_node_pool_1db0c(void);

#endif
