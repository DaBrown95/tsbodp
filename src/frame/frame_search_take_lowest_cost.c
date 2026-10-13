#include "frame_search_cost.h"

unsigned int frame_search_take_lowest_cost(struct FrameSearchRecord *output,
                                         unsigned int queue)
{
    struct FrameSearchNode *best = g_frame_search_queues[queue].first;
    struct FrameSearchNode *node = best->next;
    while (node) {
        struct FrameSearchNode *next = node->next;
        if (node->record.cost < best->record.cost)
            best = node;
        node = next;
    }
    if (best) {
        unsigned int owner_queue;
        *output = best->record;
        owner_queue = best->record.queue;
        if (g_frame_search_queues[owner_queue].last == best)
            g_frame_search_queues[owner_queue].last = best->previous;
        frame_pool_release(&g_frame_search_free_nodes[owner_queue],
                           (struct FrameObjectList *)&g_frame_search_queues[owner_queue],
                           (struct FrameObject *)best);
        return 1;
    }
    return 0;
}
