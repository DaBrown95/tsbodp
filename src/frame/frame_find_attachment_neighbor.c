#include "frame_tick.h"
#include "frame_actor_state.h"
#include "frame_actor_target_cells.h"

/* Distinct from the sixteen-byte grid-neighbor table at 0x0807F410. */
extern unsigned char g_frame_attachment_neighbor_offsets[];

union NeighborCellView {
    unsigned int word;
    struct { unsigned int x : 8, y : 8, unknown : 16; } axes;
};

unsigned char frame_find_attachment_neighbor(void *context,
                                             struct FrameObject *actor,
                                             unsigned int unused,
                                             unsigned char attachment,
                                             int *output)
{
    struct FramePoint attached, position;
    union NeighborCellView actor_cell, attached_cell, candidate;
    int dx, dy;
    unsigned int direction, index;

    frame_attachment_position(actor, attachment, &attached);
    frame_point_to_integer(&attached, &attached);
    frame_grid_point_to_cell(context, &attached,
                            (struct FrameActorPackedCell *)&attached_cell);
    frame_point_to_integer(&actor->position, &position);
    // BUG: actor_cell axes are read unset if this projection fails.
    frame_grid_point_to_cell(context, &position,
                            (struct FrameActorPackedCell *)&actor_cell);
    dx = attached.x - position.x;
    dy = attached.y - position.y;
    if (dx > 0) {
        direction = 1;
        if (dy >= 0) direction = 2;
    } else {
        direction = 3;
        if (dx < 0 && dy <= 0) direction = 0;
    }
    direction *= 2;
    for (index = direction; index < direction + 8; index++) {
        unsigned char *data;
        unsigned int occupied, terrain;

        candidate.axes.x = actor_cell.axes.x +
            g_frame_attachment_neighbor_offsets[index * 2];
        candidate.axes.y = actor_cell.axes.y +
            g_frame_attachment_neighbor_offsets[index * 2 + 1];
        data = frame_grid_cell_data_pointer(context, (int *)&candidate);
        occupied = data ? ((struct FrameGridCellProperties *)data)->occupied : 0;
        if (!(occupied & 13)) {
            data = frame_grid_cell_data_pointer(context, (int *)&candidate);
            terrain = data ? ((struct FrameGridCellProperties *)data)->terrain : 0;
            if (terrain & 2) {
                /* The original transfers four bytes, although only x/y are set.
                 * Copy the object representation without interpreting its tail. */
                __builtin_memcpy(output, &candidate, sizeof candidate);
                return 1;
            }
        }
    }
    return 0;
}
