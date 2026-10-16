#ifndef FRAME_ACTOR_24420_H
#define FRAME_ACTOR_24420_H

#include "frame_actor_group.h"
#include "view_math.h"

/* This constructor's first argument occupies r0/r1 as one position record.
 * Its gameplay role and the installed step callback remain provisional. */
struct FrameObject *frame_create_actor_24420(struct FramePoint, int);
void frame_actor_step_24968(struct FrameObject *);
void frame_actor_update_24720(struct FrameObject *);

/* Shared vector providers used by the movement helper. */
void frame_make_direction_vector(struct FramePoint *, unsigned int, int);
int frame_approximate_vector_length(struct FramePoint);
extern struct FramePoint g_frame_direction_16[];

extern struct FrameSpriteVariant **g_actor_24420_part0_tables[];
extern struct FrameSpriteVariant ***g_actor_24420_part1_tables[];
extern struct FrameSpriteVariant *g_actor_24420_part2_variants[];
extern const unsigned char g_actor_24420_palette_by_id[];
extern signed char g_frame_scene_double_direction_variants[];

struct CollisionObject;
struct FrameActor24420CollisionView {
    unsigned char unknown_00[0xc8];
    void (*collision)(struct CollisionObject *, struct CollisionObject *);
};

struct FrameObject *frame_allocate_scene_object(void);
void frame_enable_object_flags(struct FrameObject *, unsigned int);
void frame_disable_object_flags(struct FrameObject *, unsigned int);
void frame_actor_contact_24a08(struct CollisionObject *, struct CollisionObject *);
void frame_enable_animation_part(struct FrameObject *, unsigned char);
void frame_scene_player_collision(struct CollisionObject *, struct CollisionObject *);

#endif
