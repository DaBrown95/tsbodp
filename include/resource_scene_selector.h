#ifndef RESOURCE_SCENE_SELECTOR_H
#define RESOURCE_SCENE_SELECTOR_H
#include "frame_scene_player.h"
#include "resource_object_payload.h"
#include "save_stream.h"
#include "display_time_format.h"
#include "display_text_fields.h"
#include "frame_actor_state.h"
#include "frame_actor_scene.h"

/* Observed selector-factory view, distinct from registered bounds at +0xbc. */
struct ResourceSceneSelector {
    struct FrameObject *next, *previous;
    unsigned short id, subtype;
    unsigned int flags;
    unsigned char unknown10[3], player_index, unknown14[4];
    struct FramePoint position, next_position, velocity, acceleration, destination;
    unsigned char unknown40[12];
    unsigned char unknown4c, state, variant_state, pending_updates;
    unsigned char scan_flags, unknown51[7];
    int countdown;
    unsigned char unknown5c[8];
    unsigned short selector;
    unsigned char parameter, first_hour, second_hour, unknown69[31];
    void (*on_step)(struct FrameObject *);
    void (*on_remove)(struct FrameObject *);
    struct FrameObject *indicator, *animation_source;
    void (*before_step)(struct FrameObject *);
    unsigned char unknown9c[19], collision_count;
    signed char collision_x0, collision_x1, collision_y0, collision_y1;
    unsigned char collision_kind, unknownb5[19];
    void (*on_interact)(struct FrameObject *, struct FrameObject *);
    unsigned char unknowncc[4];
    struct FrameOam oam;
};
struct ResourceSceneSelectorPayload {
    unsigned int id;
    short x, y;
    unsigned char half_width, half_height, parameter, selector, subtype;
};
extern unsigned int g_scene_id;
extern struct FrameVariantResource g_resource_selector_animation2;
extern struct FrameVariantResource g_resource_selector_animation3;
extern struct FrameVariantResource g_resource_selector_animation4;
extern struct FrameVariantResource g_resource_selector_animation5;
struct FrameObject *frame_allocate_scene_object(void);
void frame_enable_object_flags(struct FrameObject *, unsigned int);
void frame_acquire_palette_slot(struct FrameObject *, int);
void resource_scene_selector_tick(struct FrameObject *);
void resource_scene_selector_interact(struct FrameObject *, struct FrameObject *);
void resource_scene_selector_interact_alternate(struct FrameObject *, struct FrameObject *);
union ResourceSelectorClock {
    struct DisplayTimeRecord record;
    unsigned int words[2];
    struct { unsigned int day : 16, hour : 8, minute : 8; unsigned int tail; } fields;
};
/* Same world root as the clock and scene-player views; roles remain provisional. */
struct ResourceSelectorWorld {
    unsigned char unknown00[8];
    struct DisplayTimeRecord clock;
    unsigned char unknown10[0x41e], mode42e, flag42f;
    unsigned char unknown430[0x318], selected_actor;
};
struct ResourceSelectorNotice { unsigned char unknown00, mode, kind, unknown03, active; };
extern const struct DisplayTimeRecord g_resource_selector_clock;
extern struct FrameObject *g_frame_scene_active_actor;
extern struct ResourceSelectorWorld g_resource_selector_world;
extern struct ResourceSelectorNotice g_resource_selector_notice;
extern const unsigned short g_resource_selector_labels[];
void resource_scene_selector_release_player(struct FrameObject *);
void resource_scene_selector_complete(struct FrameObject *);
unsigned char frame_object_has_flags(struct FrameObject *, unsigned int);
void frame_disable_object_flags(struct FrameObject *, unsigned int);
void frame_set_variant_state(struct FrameObject *, unsigned char);
#include "resource_actor_selection.h"
void scene_submit_default_request(unsigned int);
struct FrameObject *resource_create_scene_selector(unsigned char, unsigned char);
struct SceneRequest;
extern struct SceneRequest g_scene_previous_request;
void frame_stop_motion(struct FrameObject *);
unsigned char frame_scene_effect_facing_available(struct FrameObject *, struct FrameObject *);
void resource_scene_selector_activate_player(struct FrameObject *, int, int, unsigned short);
unsigned int audio_play_animation_cue(unsigned int);
#endif
