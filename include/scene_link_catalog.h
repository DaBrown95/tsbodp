#ifndef SCENE_LINK_CATALOG_H
#define SCENE_LINK_CATALOG_H
#include "link_event_receive.h"
#include "display_scene_lifecycle.h"
#include "display_catalog_presentation.h"
#include "display_catalog_text.h"
#include "display_text_fields.h"
#include "save_world_view_resources.h"
#include "scene_view_frame.h"
#include "frame_actor_idle.h"
#include "audio_game.h"
#include "input.h"
#include "resource_condition_entries.h"
#include "actor_entry_collection.h"

/* Observed access prefixes; complete dynamic storage and names are provisional. */
#include "scene_link_catalog_world.h"
struct SceneLinkCatalogActor {
    unsigned char unknown00[77], state, unknown4e[26], selected, unknown69[3];
    unsigned int selected_index;
};
struct SceneLinkCatalogOwners {
    struct FrameObject *first, *entries[8], *captions[5], *details[2];
};
struct SceneLinkCatalogInput {
    struct FrameObject *actor;
    unsigned char unknown04[44], player_count, local_player;
};
struct SceneLinkCatalogCaption { unsigned char x, y, unknown02[2]; };
struct SceneLinkCatalogDefinition { unsigned int object_id; unsigned char unknown04[20]; };
extern struct SceneLinkCatalogOwners g_scene_link_catalog_owners;
extern struct SceneLinkCatalogInput g_scene_link_catalog_input;
extern unsigned char g_scene_link_catalog_quantity_limit;
extern unsigned char g_scene_catalog_quantities[9];
extern const struct SceneLinkCatalogCaption g_scene_link_catalog_captions[5];
extern const struct SceneLinkCatalogDefinition g_scene_link_catalog_definitions[];
extern const unsigned int g_scene_link_catalog_control3, g_scene_link_catalog_control2;
extern const unsigned int g_scene_link_catalog_control1, g_scene_link_catalog_control0;
extern const struct BackgroundResource g_scene_link_catalog_background2;

void display_enable_layers(unsigned short);
unsigned int display_load_resource_palette(const struct BackgroundResource *, unsigned short);
void transition_run_first(unsigned short, unsigned int), transition_run_second(unsigned short, unsigned int);
void transition_fade_black_in_record(unsigned short), transition_fade_black_out_record(unsigned short);
void scene_link_catalog_initialize(void), scene_link_catalog_shutdown(void);
unsigned int scene_link_catalog_try_entry(struct FrameObject *, unsigned int);
void scene_link_catalog_draw_quantity(void), scene_link_catalog_draw_panel(unsigned int);
/* Controller and connected interfaces; builder and accept handlers remain original. */
void scene_link_catalog_build(void), scene_link_catalog_step(void);
void scene_link_catalog_accept_entry(void), scene_link_catalog_accept_quantity(void);
void scene_submit_default_request(unsigned int);
#endif
