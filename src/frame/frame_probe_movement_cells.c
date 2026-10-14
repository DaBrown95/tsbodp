#include "frame_movement_cells.h"

void frame_probe_movement_cells(struct FrameObject *object, void *registration)
{
    struct FramePoint velocity;
    union FrameMovementCellPoint point;
    struct FrameActorPackedCell cell;
    unsigned int flags = object->flags;
    unsigned int mask = 0xffff;
    int blocked = 0;
    int direction = ((struct FrameMovementDirection *)object)->direction - 1;
    int i;
    const struct FramePoint *next;

    if (direction < 0)
        direction = ((struct FrameMovementDirection *)object)->direction + 7;
    i = 0;
    next = &object->next_position;
    for (; i <= 2; i++) {
        if (direction == ((struct FrameMovementDirection *)object)->direction)
            frame_make_velocity(&velocity, flags, direction, 0x80000);
        else
            frame_make_velocity(&velocity, flags, direction, 0x40000);
        frame_add_points(&velocity, next, &point.point);
        point.point.x >>= 16;
        point.point.y = point.half[3];
        if (!frame_grid_point_to_cell(registration, &point.point, &cell))
            return;
        {
            register unsigned int current_cell asm("r0") =
                ((struct FrameActorPackedCellView *)object)->cell.index;
            register unsigned int next_cell asm("r2") = cell.index;

            if ((current_cell & mask) != (next_cell & mask)) {
                unsigned int occupancy = frame_grid_occupancy(
                    registration, (const int *)&cell);
                unsigned int terrain = frame_grid_terrain(
                    registration, (const int *)&cell);
                unsigned int masked = occupancy & 0x2d;
                unsigned int occupied = (-masked | masked) >> 31;
                unsigned int marked = (occupancy >> 4) & 1;
                unsigned int mode = (flags >> 24) & 1;
                unsigned int collision = (flags >> 6) & 1;
                unsigned int surface = (flags >> 4) & 1;

                if (collision == 1 && occupied == 1 && mode == 0) {
                    blocked = 1;
                    break;
                }
                if (surface == 1 && marked == 1) {
                    blocked = 1;
                    break;
                }
                if (mode == 0 && (flags & 0x10000) && !(terrain & 2)) {
                    blocked = 1;
                    break;
                }
            }
        }
        ++direction;
        if (direction > 7)
            direction -= 8;
    }
    if (blocked == 1) {
        frame_need_effect_stop_at_position(object);
        frame_apply_movement_contact(object, 37);
    }
}
