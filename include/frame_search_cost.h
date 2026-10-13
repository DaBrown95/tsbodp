#ifndef FRAME_SEARCH_COST_H
#define FRAME_SEARCH_COST_H

#include "frame_search.h"

/* Same 24-byte node and 16-byte payload as the priority-based queue pop. */
unsigned int frame_search_take_lowest_cost(struct FrameSearchRecord *, unsigned int);

#endif
