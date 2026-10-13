#include "frame.h"
#include "frame_actor_grid.h"

static inline int path_cell_at_offset(struct FrameGridSearchState *state,
                                     int byte_offset)
{
    int *cells = state->cells;
    return *(int *)(byte_offset + (unsigned int)cells);
}

unsigned char frame_copy_grid_path(struct FramePoint *output,
                                  unsigned int unused)
{
    int count = g_frame_grid_search.count;
    if (count) {
        struct FrameGridSearchState *state = &g_frame_grid_search;
        int byte_offset = count * 4 - 4;
        struct FramePoint *cursor = output;
        do {
            int cell;
            struct FramePoint point;
            count--;
            cell = path_cell_at_offset(state, byte_offset);
            frame_grid_cell_to_point(state->context, &cell, &point);
            *cursor++ = point;
            byte_offset -= 4;
        } while (count);
    }
    return 1;
}

asm(".align 2, 0");
