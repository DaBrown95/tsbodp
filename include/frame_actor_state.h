#ifndef FRAME_ACTOR_STATE_H
#define FRAME_ACTOR_STATE_H

struct FrameObject;
struct FramePoint;

/* Selector-specific work fields. Other actor views overlap these addresses. */
struct FrameActorStateWork {
 unsigned char unknown_00[84];
 unsigned int movement_status;
 int timer;
 unsigned char unknown_5c[8];
 unsigned char waypoint_group, waypoint_index, wait_units, unknown_67;
 unsigned int cue_handle;
};

unsigned char resource_group_point_count(unsigned char);
struct FrameActorGroupPoint { short x, y; unsigned char unknown_04[4]; };
extern unsigned char *g_actor_point_group_data;
struct FramePoint resource_read_group_point(unsigned char, unsigned char);
int frame_random_range(int, int);
unsigned char frame_begin_actor_route(struct FrameObject *, struct FramePoint *, unsigned int *, unsigned int, unsigned char);
void frame_cancel_actor_route(struct FrameObject *);
unsigned char frame_find_need_target(struct FrameObject *, void **, unsigned int *);
unsigned char frame_actor_use_target(void *, struct FrameObject *, unsigned char);
unsigned char frame_find_scene_target(int *, int *);
/* Further state views retain unspecified bytes and selector-specific roles. */
union ResourceGameState;
extern union ResourceGameState g_resource_game_state;
struct FrameActorClockState { unsigned char unknown_00[10], clock; };
struct FrameActorContactWork { unsigned char unknown_00[172]; unsigned short contact; };
struct FrameActorGridCell { unsigned char unknown_00[196]; int cell; };
extern unsigned char g_actor_wander_directions[], g_actor_reverse_directions[];
unsigned char frame_actor_choose_walk_direction(struct FrameObject *);
void frame_actor_refresh_terrain(struct FrameObject *);
void frame_route_enable_destination(struct FrameObject *);
void frame_route_set_limit(struct FrameObject *, unsigned char);
unsigned char frame_find_action_target(struct FrameObject *, unsigned char, void **);
unsigned char frame_random_chance(unsigned char);
void frame_grid_neighbor(void *, const int *, int *, unsigned char);
unsigned int frame_grid_terrain(void *, const int *);
unsigned int frame_grid_occupancy(void *, const int *);
unsigned char frame_actor_direction_available(struct FrameObject *, unsigned char);
void frame_set_actor_direction(struct FrameObject *, unsigned char);
unsigned char frame_direction_toward(struct FrameObject *, struct FrameObject *);
unsigned char frame_direction_to_destination(struct FramePoint, struct FramePoint, int);
void frame_clear_animation_pending(struct FrameObject *);
void frame_add_points(const struct FramePoint *, const struct FramePoint *, struct FramePoint *);
void frame_point_to_integer(const struct FramePoint *, struct FramePoint *);
void frame_point_to_fixed(const struct FramePoint *, struct FramePoint *);
/* Availability compares the low halfword; the upper half remains unspecified. */
struct FrameActorPackedCell { unsigned short index, unknown; };
struct FrameActorPackedCellView { unsigned char unknown[196]; struct FrameActorPackedCell cell; };
void frame_grid_point_to_cell(void *, const struct FramePoint *, struct FrameActorPackedCell *);

/* Selector-derived names; the handlers' gameplay roles remain provisional. */
void frame_run_actor_state(struct FrameObject *);
void frame_actor_state_7(struct FrameObject *);
void frame_actor_state_8(struct FrameObject *);
void frame_actor_state_9(struct FrameObject *);
void frame_actor_state_13(struct FrameObject *);
void frame_actor_state_16(struct FrameObject *);
void frame_actor_state_24(struct FrameObject *);
void frame_actor_state_26(struct FrameObject *);
void frame_actor_state_17(struct FrameObject *);
void frame_actor_state_19(struct FrameObject *);
void frame_actor_state_22(struct FrameObject *);
void frame_actor_state_23(struct FrameObject *);
void frame_actor_state_25(struct FrameObject *);
void frame_actor_state_37(void);
void frame_actor_state_27(struct FrameObject *);
void frame_actor_state_28(struct FrameObject *);
void frame_actor_state_34(struct FrameObject *);
void frame_actor_state_31_32_33(struct FrameObject *);
void frame_actor_state_35(struct FrameObject *);
void frame_actor_state_36(struct FrameObject *);
void frame_actor_state_38(void);
void frame_actor_state_39(struct FrameObject *);
void frame_actor_state_40(struct FrameObject *);
void frame_actor_state_42(struct FrameObject *);
void frame_actor_state_41(struct FrameObject *);
void frame_actor_state_43(struct FrameObject *);
void frame_actor_state_44(struct FrameObject *);
void frame_actor_state_45(struct FrameObject *);
void frame_actor_state_46(struct FrameObject *);
void frame_actor_state_47(struct FrameObject *);

#endif
