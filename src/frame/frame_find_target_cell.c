#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "frame_actor_choices.h"
#include "frame_actor_target_cells.h"

struct FrameGridCellBits {
    unsigned char terrain : 2, occupied : 6;
} __attribute__((packed));

union ActorCellView {
    struct FrameActorPackedCell cell;
    unsigned short half;
    unsigned char bytes[4];
    unsigned int word;
};

union TargetCellView {
    unsigned int word;
    int provider_cell;
    unsigned short half;
    struct {
        unsigned int x : 8, y : 8, unknown : 16;
    } axes;
};

static __inline unsigned int target_axes_allowed(
    struct FrameActorTargetCellOwner *owner, unsigned int candidate_word)
{
    unsigned int allowed = 0;
    unsigned int limit = frame_actor_owner_cell_count(owner, 1), j;
    unsigned int *restricted = owner->cells + 12;
    register unsigned int candidate_high asm("r4");

    for (j = 0; j < limit; j++) {
        register unsigned int cell_word asm("r1") = restricted[j];
        if ((unsigned char)candidate_word == (unsigned char)cell_word)
            goto permitted;
        {
            register unsigned int shifted asm("r0") = cell_word >> 8;
            register unsigned int coordinate asm("r1");
            candidate_high = candidate_word << 16;
            coordinate = candidate_high >> 24;
            shifted = (unsigned char)shifted;
            if (coordinate != shifted)
                continue;
        }
permitted:
        allowed = 1;
        break;
    }
    return allowed;
}

unsigned char frame_find_target_cell(
    void *context, struct FrameObject *actor, struct FrameObject *target,
    int *output, unsigned char restrict_axes)
{
    struct FrameActorTargetCellOwner *owner = ((struct FrameActionTargetOwner *)target)->owner;
    struct FramePoint point;
    union ActorCellView actor_cell;
    union TargetCellView candidate;
    unsigned int best;
    unsigned int i;
    unsigned int count;
    int cell_mask;
    unsigned int selected;
    unsigned int found;

    frame_point_to_integer(&actor->position, &point);
    // BUG: actor_cell is unset if projection fails, but the search still reads it.
    frame_grid_point_to_cell(context, &point, &actor_cell.cell);
    found = 0;
    best = 10000;
    count = frame_actor_owner_cell_count(owner, 4);
    for (i = 0; i < count; i++) {
        candidate.word = owner->cells[i];
        if (restrict_axes) {
            if (!target_axes_allowed(owner, candidate.word))
                continue;
        }
        cell_mask = 0xffff;
        {
            register unsigned short loaded_actor asm("r3") = actor_cell.half;
            register unsigned int wide_actor asm("r3") = loaded_actor;
            register unsigned short loaded_candidate asm("r1") = candidate.half;
            register unsigned int wide_candidate asm("r1") = loaded_candidate;
            register unsigned int masked_actor asm("r0") = cell_mask;
            register unsigned int other_mask asm("r3");
            register unsigned int masked_candidate asm("r1");
            masked_actor &= wide_actor;
            other_mask = cell_mask;
            masked_candidate = wide_candidate & other_mask;
            if (masked_actor == masked_candidate) {
                selected = candidate.word;
                found = 1;
                break;
            }
        }
        {
            unsigned char *data = frame_grid_cell_data_pointer(context, &candidate.provider_cell);
            unsigned int terrain = data ? ((struct FrameGridCellBits *)data)->terrain : 0;
            unsigned int occupied;
            data = frame_grid_cell_data_pointer(context, &candidate.provider_cell);
            occupied = data ? ((struct FrameGridCellBits *)data)->occupied : 0;
            if ((terrain & 2) && !(occupied & 0x3d)) {
                unsigned int distance;
                int dx, dy;
                dx = actor_cell.bytes[0] - ((unsigned char *)&candidate)[0];
                if (dx < 0)
                    dx = -dx;
                point.x = dx;
                dy = actor_cell.bytes[1] - ((unsigned char *)&candidate)[1];
                if (dy < 0)
                    dy = -dy;
                point.y = dy;
                distance = dx + dy;
                if (distance < best) {
                    best = distance;
                    selected = owner->cells[i];
                    found = 1;
                }
            }
        }
    }
    // BUG: selected is unset if no candidate is accepted, but its bytes are still written.
    ((unsigned char *)output)[0] = selected;
    ((unsigned char *)output)[1] = selected >> 8;
    return found;
}
asm(".align 2, 0");
