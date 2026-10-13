#ifndef RESOURCE_TIMED_ACTOR_H
#define RESOURCE_TIMED_ACTOR_H

#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "resource_object_payload.h"
#include "display_time.h"
#include "frame_random.h"
#include "view_math.h"

/* Twelve bytes copied as one record; individual word meanings are unknown. */
struct ResourceTimedWork { unsigned int words[3]; };
/* Partial object view through its observed OAM fields, not its allocation size. */
struct ResourceTimedActor {
    struct FrameObject *next, *previous;
    unsigned short id, subtype;
    unsigned int flags;
    unsigned char owner_group, owner_slot, direction, unknown13;
    int speed;
    struct FramePoint position, next_position, velocity, acceleration, destination;
    struct ResourceTimedWork work;
    unsigned char kind, state, variant_state, pending_updates, unknown50[8];
    int countdown;
    unsigned short unknown5c, timer;
    void *actor_state;
    unsigned char unknown64[4];
    unsigned short timer68, timer6a, timer6c, timer6e;
    unsigned char unknown70[20], mode84, unknown85[3];
    void (*on_step)(struct FrameObject *);
    void (*on_remove)(struct FrameObject *);
    struct FrameObject *indicator, *animation_source;
    void (*before_step)(struct FrameObject *);
    unsigned char unknown9c[18], unknown_ae, unknownaf[25];
    void (*on_interact)(struct FrameObject *, struct FrameObject *);
    unsigned char unknowncc[4];
    struct FrameOam oam;
};
struct ResourceTimedActorPayload {
    int id;
    short x, y;
    unsigned char kind, direction, group, slot;
};
struct ResourceTimedAnimation {
    struct FrameVariantResource *moving, *idle;
};
extern struct ResourceTimedAnimation g_resource_timed_animations[];
extern const struct ResourceTimedWork g_resource_timed_initial_work;
extern struct DisplayTimeRecord g_resource_timed_start, g_resource_timed_end;
extern struct DisplayTimeRecord g_display_world_clock;
void frame_enable_object_flags(struct FrameObject *, unsigned int);
void frame_disable_object_flags(struct FrameObject *, unsigned int);
void frame_set_variant_state(struct FrameObject *, unsigned char);
void frame_stop_motion(struct FrameObject *);
void resource_activate_groups(unsigned char, unsigned char);
void resource_timed_actor_tick(struct FrameObject *);
void resource_timed_actor_patrol(struct FrameObject *);
void resource_timed_actor_interact(struct FrameObject *, struct FrameObject *);
void resource_timed_actor_choose_destination(struct FrameObject *, unsigned int);

void frame_acquire_palette_slot(struct FrameObject *, int);
extern struct FrameObject *g_need_effect_player;
unsigned char frame_direction_away(struct FrameObject *, struct FrameObject *);
struct FrameObject *resource_create_timed_actor(unsigned char, unsigned char);

#endif
