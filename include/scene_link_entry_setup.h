#ifndef SCENE_LINK_ENTRY_SETUP_H
#define SCENE_LINK_ENTRY_SETUP_H
#include "link_entry_receive.h"
#include "display_scene_lifecycle.h"
#include "display_catalog_text.h"
#include "save_world_view_resources.h"
#include "save_game_serialization.h"
#include "resource_conditions.h"
#include "frame_random.h"
#include "display_time_hud.h"

/* Read-only four-byte coordinate prefix; no complete table capacity asserted. */
struct SceneLinkSelectionCaption {
    unsigned char x, y, unknown02[2];
};
extern const struct SceneLinkSelectionCaption g_scene_link_selection_captions[];
extern const unsigned char g_scene_link_selection_palettes[];
extern const unsigned int g_scene_link_entry_control_unlinked;
extern const unsigned int g_scene_link_entry_control_linked;
extern const unsigned int g_scene_link_entry_control1;
extern const unsigned int g_scene_link_entry_text_control;
/* Existing canonical readonly declarations, not new mutable owners. */
extern const unsigned short g_display_menu_palette_data[];
extern const struct BackgroundResource g_display_menu_palette_resource;
extern const struct BackgroundResource g_scene_link_entry_background_unlinked;
extern const struct BackgroundResource g_scene_link_entry_background_linked;
extern const struct BackgroundResource g_scene_link_entry_background1;
extern const struct BackgroundResource g_scene_link_entry_palette4;
extern const struct BackgroundResource g_scene_link_entry_palette5;
extern const struct BackgroundResource g_scene_link_entry_palette6;
void transition_run_first(unsigned short, unsigned int);
void transition_fade_black_in_record(unsigned short);
void scene_link_entry_build_linked_objects(void);
void scene_link_entry_refresh_linked_offers(void);
void scene_link_entry_draw_quantities(void);
void scene_link_entry_draw_linked_quantities(void);
/* Explicit original service boundaries. No reconstructed C is claimed. */
void scene_link_entry_build_objects_original(void);
void scene_link_entry_refresh_offers_original(void);
void scene_link_entry_prepare_original(void);
void scene_link_entry_draw_panel_original(void);
void scene_link_entry_initialize(void);
#endif
