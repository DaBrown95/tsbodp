#include "save_world_display.h"

/* Keep the observed slot byte offset separate from the row base. */
static inline struct FrameObject *save_world_row_object(
    struct SaveWorldTransitionRow *row, unsigned int offset)
{
    register unsigned int address asm("r0");
    address = (unsigned int)row;
    address += 0x10;
    address += offset;
    return *(struct FrameObject **)address;
}

void save_world_update_row_gauges(void)
{
    struct FrameActorNeedState *needs =
        (struct FrameActorNeedState *)g_frame_actor_local_need_state;
    struct SaveWorldTransitionRow *row =
        &g_save_world_transition_rows[g_display_world_clock_selection.row];
    unsigned int index = 0;
    register unsigned int slot_offset asm("r9") = 0;
    const struct SaveWorldIndicatorCoordinate *coordinate =
        g_save_world_indicator_coordinates;
    do {
        if ((row->flags & (4u << index)) ||
            row->unknown30[index] != frame_actor_need_value(
                (struct FrameActorNeedState *)g_frame_actor_local_need_state, index)) {
            int scale;
            row->unknown30[index] = frame_actor_need_value(
                (struct FrameActorNeedState *)g_frame_actor_local_need_state, index);
            scale = save_world_scale_gauge(frame_actor_need_value(needs, index), 100, 19);
            display_copy_background_rectangle(0, g_save_world_gauge_map, 0, scale * 3,
                coordinate->x, coordinate->y, 1, 3, 0x1036);
        }
        if (row->ticks == 0 && (row->flags & (0x400u << index))) {
            if (!save_world_row_object(row, slot_offset))
                save_world_create_row_indicator(row, index);
        } else {
            if (save_world_row_object(row, slot_offset))
                save_world_release_row_object(row, index);
        }
        slot_offset += 4;
        ++coordinate;
        ++index;
    } while (index <= 7);
    row->flags &= 0xfffc0003u;
}
