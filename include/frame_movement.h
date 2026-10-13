#ifndef FRAME_MOVEMENT_H
#define FRAME_MOVEMENT_H
#include "frame.h"
#include "frame_actor_state.h"
#include "frame_layer.h"
#include "view_math.h"

/* Access views for the movement-contact path, not complete object layouts. */
struct FrameMovementDirection {
    unsigned char unknown_00[18], direction;
};
struct FrameMovementResponse {
    unsigned char unknown_00[132], response, terrain;
};
struct FrameMovementPending {
    unsigned char unknown_00[79], pending;
};
extern unsigned int g_frame_movement_filter[2];
extern const int g_frame_movement_large_bounds[4];
extern const int g_frame_movement_small_bounds[4];
extern unsigned char g_frame_movement_reverse_directions[];

unsigned char frame_object_has_flags(struct FrameObject *, unsigned int);
void frame_collect_movement_contacts(struct FrameObject *);
void frame_refresh_movement_contacts(struct FrameObject *);
unsigned int frame_get_movement_probe_bounds(struct FrameObject *, int *);
unsigned int frame_forward_movement_contact(struct FrameObject *, unsigned int);
void frame_apply_movement_contact(struct FrameObject *, unsigned int);
/* A nonzero return means the offset was rejected and restored. The two-word
 * displacement is passed in R1/R2 after the object pointer in R0. */
unsigned char frame_movement_offset_blocked(struct FrameObject *, struct FramePoint);
unsigned char frame_movement_direction_blocked(struct FrameObject *, struct FramePoint);

unsigned int frame_probe_movement_edge(unsigned int, const int *);

/* Connected original regions remain explicit until their C extent matches. */
void frame_probe_movement_cells(struct FrameObject *, void *);
void frame_redirect_movement(struct FrameObject *, unsigned int);
unsigned int frame_map_terrain_at(struct FramePoint);
void frame_set_variant_state(struct FrameObject *, unsigned char);
void frame_need_effect_stop_at_position(struct FrameObject *);

static inline unsigned int frame_movement_is_contact(unsigned int contact)
{
    return contact - 2 <= 33;
}
#endif
