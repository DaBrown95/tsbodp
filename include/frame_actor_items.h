#ifndef FRAME_ACTOR_ITEMS_H
#define FRAME_ACTOR_ITEMS_H

#include "frame_actor_24420.h"
#include "frame_transient_effect.h"
#include "frame_random.h"
#include "display_time.h"
#include "display_menu_relation.h"
#include "audio_game.h"

/* Partial activity-row-zero views. Names describe these item producers and
 * callbacks; neither the complete scene state nor its caller domains is known. */
struct FrameActorItemState {
    struct FrameObject *primary;
    unsigned char unknown_04[8];
    short created_count;
    unsigned short collected_count;
    unsigned char unknown_10[3], option, phase, flags;
};
struct FrameActorItemOption {
    struct DisplayTimeRecord clock;
    int speed;
    unsigned char count2, count3, count4, count_other, reward;
};
struct FrameActorItemDisplay {
    unsigned char unknown_00[0xd1];
    unsigned char mode : 2, contact_mode : 2, unknown_d1_4 : 1;
    unsigned char double_size : 1, unknown_d1_6 : 2;
    unsigned char unknown_d2;
    unsigned char unknown_d3_0 : 4, special : 1, unknown_d3_5 : 3;
    unsigned char tile_low;
    unsigned char tile_high : 2, layer : 2, palette : 4;
};

struct SceneContactState;
extern struct SceneContactState *g_scene_contact_state;
extern const struct FrameActorItemOption g_frame_actor_item_options[];
extern unsigned char g_frame_transient_extended_directions[];
extern const struct FramePoint g_frame_actor_item_water_points[];
extern struct FrameVariantResource g_frame_actor_item_resource2;
extern struct FrameVariantResource g_frame_actor_item_resource3;
extern struct FrameVariantResource g_frame_actor_item_resource4;
extern struct DisplayMenuRelationState g_display_menu_relation_state;
extern struct DisplayTimeRecord g_display_countdown;

void frame_create_actor_item(unsigned int, unsigned char *);
void frame_place_actor_item_in_water(struct FrameObject *, unsigned char *);
void frame_place_actor_item_on_land(struct FrameObject *);
void frame_step_actor_item_visibility(struct FrameObject *);
void frame_emit_actor_item_contact(struct FrameObject *, unsigned char);
void frame_actor_item_contact_collect(struct CollisionObject *, struct CollisionObject *);
void frame_actor_item_contact_penalty(struct CollisionObject *, struct CollisionObject *);
void frame_actor_item_contact_relation(struct CollisionObject *, struct CollisionObject *);

void frame_acquire_palette_slot(struct FrameObject *, int);
unsigned int frame_map_terrain_at(struct FramePoint);
void scene_contact_add_activity_score(int);

#endif
