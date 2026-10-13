#ifndef FRAME_OPTIONAL_VIEW_H
#define FRAME_OPTIONAL_VIEW_H

#include "frame_optional_choice_context.h"
#include "resource_object_payload.h"

/* Twenty-byte payload span observed by factory row 14. Wider allocation,
 * serialized instances and payload ownership have not been established. */
struct FrameOptionalViewPayload {
    unsigned int id;
    short x, y;
    unsigned short view_x, view_y;
    unsigned char bound_x, bound_y, first_transition, second_transition;
    unsigned char objects_group, program_group, direction, unknown_13;
};
/* Selector-specific object view. Bounds at B0..B3 are distinct from the
 * general object's BC..BF bounds. The callback stores establish 88 and C8. */
struct FrameOptionalViewObject {
    struct FrameObject *next, *previous;
    unsigned short id, unknown_0a;
    unsigned int flags;
    unsigned char owner_id, owner_slot, direction, unknown_13[0x3a];
    unsigned char state, variant, pending, unknown_50[14];
    unsigned short delay;
    unsigned char unknown_60[4];
    struct FrameObject *actor;
    unsigned short view_x, view_y;
    unsigned char resource_loaded, first_transition, second_transition, actor_direction;
    unsigned char unknown_70[24];
    void (*on_step)(struct FrameObject *);
    unsigned char unknown_8c[36];
    signed char bound_x0, bound_x1, bound_y0, bound_y1;
    unsigned char unknown_b4[20];
    void (*on_interact)(struct FrameObject *, struct FrameObject *);
};
/* The constructor writes one to each byte. Their broader roles are provisional. */
struct FrameOptionalViewCollisionFlags {
    unsigned char unknown_00[0xaf];
    unsigned char flag_af, unknown_b0[4], flag_b4;
};
/* Bounded alias of the established view context at 030040E0. */
struct FrameOptionalViewContext {
    unsigned char unknown_00[0x31];
    unsigned char current_view;
};
extern struct FrameOptionalViewContext g_optional_view_context;

struct FrameObject *frame_create_optional_view_object(unsigned char, unsigned char);
void frame_optional_view_step(struct FrameObject *);
void frame_optional_view_interact(struct FrameObject *, struct FrameObject *);

struct TransitionViewObject;
struct FrameObject *frame_allocate_scene_object(void);
void resource_activate_groups(unsigned char, unsigned char);
void transition_set_view_mode(unsigned int, unsigned char);
void transition_set_view_position(struct FramePoint, unsigned char);
void transition_configure_view(struct TransitionViewObject *, struct FramePoint, unsigned char);
void transition_run_first(unsigned short, unsigned int);
void transition_run_second(unsigned short, unsigned int);

#endif
