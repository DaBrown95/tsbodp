#ifndef TSBODP_FRAME_H
#define TSBODP_FRAME_H

#include "irq.h"
#include "frame_grid_cells.h"

/* Reconstructed layouts. Names are provisional and fields follow ROM accesses. */
typedef unsigned char FrameU8;
typedef unsigned short FrameU16;
typedef unsigned int FrameU32;
struct FrameDisplayPart {
    FrameU16 bytes, index;
    FrameU8 unknown_04[8];
};
struct FramePoint {
    int x, y;
};
/* Ordering coordinates observed at object +0x9C through +0xAB.
 * The remaining 16 bytes have no new typed interpretation here. */
struct FrameOrderingBounds {
    struct FramePoint lower, upper;
    FrameU8 unknown_ac[16];
};
union FrameSpatialStorage {
    FrameU8 unknown_9c[32];
    struct FrameOrderingBounds bounds;
};
union FrameMotionStorage {
    FrameU8 bytes[60];
    struct {
        FrameU8 unknown_00[18];
        FrameU16 timer;
        FrameU8 unknown_14[40];
    } motion;
};
struct FrameObject {
    struct FrameObject *next, *previous;
    FrameU16 id, unknown_0a;
    FrameU32 flags;
    FrameU8 owner_id, owner_slot;
    FrameU8 unknown_12[6];
    struct FramePoint position, next_position;
    struct FramePoint velocity, acceleration, destination;
    FrameU16 phase_x, phase_y;
    short rate_x, rate_y, amplitude_x, amplitude_y;
    union FrameMotionStorage motion_storage;
    void (*on_step)(struct FrameObject *);
    void (*on_remove)(struct FrameObject *);
    FrameU32 unknown_90;
    struct FrameObject *animation_source;
    void (*before_step)(struct FrameObject *);
    union FrameSpatialStorage spatial;
    signed char bound_x0, bound_x1, bound_y0, bound_y1;
    FrameU8 unknown_c0[4];
    FrameU8 registered_bounds[13];
    unsigned int display_mode : 2;
    unsigned char unknown_d1_2 : 3;
    unsigned char double_tile_size : 1;
    unsigned char unknown_d1_6 : 2;
    FrameU8 unknown_d2;
    unsigned char render_unknown_d3_0 : 4;
    signed char render_special : 1;
    unsigned char render_unknown_d3_5 : 3;
    unsigned short display_tile : 10;
    unsigned short display_layer : 2;
    unsigned short display_palette : 4;
    FrameU8 unknown_d6[4];
    FrameU8 shared_slot;
    FrameU8 unknown_db[31];
    FrameU16 affine_handle;
    FrameU16 display_bytes, display_index;
    FrameU8 forced_visible;
    FrameU8 sharing_flags;
    FrameU8 shared_group;
    FrameU8 unknown_103[5];
    struct FrameDisplayPart parts[4];
};
struct FrameSharedDisplay {
    FrameU8 unknown_00[8];
    FrameU16 indices[12];
    FrameU8 counts[20];
};
struct FrameQueue {
    void *backing_buffer;
    struct FrameObject *free_list;
    FrameU8 count;
    FrameU8 unknown_09[3];
    struct FrameObject *objects[128];
    FrameU8 deferred_refresh;
};
extern struct FrameQueue g_frame_queue;
extern struct FrameSharedDisplay *g_frame_shared_display;
void frame_release_display(struct FrameObject *object);
void frame_flush_display(void);
void frame_free_display_range(FrameU16 index, FrameU32 bytes, FrameU8 double_size);

struct FrameObjectList {
    struct FrameObject *first, *last;
};
extern FrameU32 g_frame_flags, g_frame_count;
extern struct FrameObjectList g_frame_primary_list;
/* Object count passed to the copied ARM collision dispatcher. */
extern FrameU32 g_frame_dispatch_arg;
extern unsigned char g_frame_dispatch_primary[], g_frame_dispatch_sort[], g_frame_dispatch_scratch[];
extern struct FrameObject *g_frame_objects[];
void frame_step_object(struct FrameObject *, FrameU8);
void frame_prepare_animation(struct FrameObject *);
void frame_advance_position(struct FrameObject *);
void frame_finalize_object(struct FrameObject *);
void frame_collect_objects(void);
struct FrameApplyObject;
void frame_apply_update(struct FrameApplyObject *, FrameU8);
FrameU8 frame_render_object(struct FrameObject *);
int frame_finish_layer(FrameU8);
void frame_commit_affine(void);

extern void *g_frame_registration;
void frame_remove_object(struct FrameObject *);
int frame_check_visibility(struct FrameObject *);
void frame_tick_animation(struct FrameObject *);
void frame_update_affine(struct FrameObject *);
void frame_integrate_velocity(struct FrameObject *);
void frame_update_bounds(struct FrameObject *);
void frame_collect_movement_contacts(struct FrameObject *);

void frame_get_view_origin(struct FramePoint *, FrameU8);
void frame_project_point(struct FramePoint *, struct FramePoint *);

extern FrameU8 g_frame_release_immediately;
void frame_release_object_palette(struct FrameObject *);
void resource_set_object(struct FrameObject *, FrameU8, FrameU8);
void frame_destroy_affine(struct FrameObject *);
void frame_recycle_object(struct FrameObject **, struct FrameObjectList *, struct FrameObject *);

int frame_sine(int);
int frame_cosine(int);

void frame_locate_bounds(void *, struct FramePoint *, void *);

#endif /* TSBODP_FRAME_H */
