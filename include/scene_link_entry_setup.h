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
extern short g_link_offer_adjustment_timer;
/* Readonly percentage windows; complete capacities remain unproved. */
extern const unsigned char g_scene_link_offer_percent_first[];
extern const unsigned char g_scene_link_offer_percent_last[];
extern const struct DisplayTimeRecord g_scene_link_offer_countdown;
/* Two-byte serialized rows observed by the native controller. */
extern const unsigned char g_link_offer_difference_limits[][2];
/* Existing canonical readonly declarations, not new mutable owners. */
extern const struct DisplayTimeRecord g_resource_selector_clock;
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
void scene_link_entry_draw_panel(void);
void scene_link_entry_draw_header_value(void);
void scene_link_entry_confirm_offer(void);
void scene_link_entry_step_offers(void);
void scene_link_entry_step_linked_offers(void);
void scene_link_entry_refresh_offers(void);
/* Explicit original service boundary. No reconstructed C is claimed. */
void scene_link_entry_build_objects_original(void);

void scene_link_entry_initialize(void);
void scene_link_entry_step(void);

/* End callback and existing transition provider boundaries. */
void transition_run_second(unsigned short, unsigned int);
void transition_fade_black_out_record(unsigned short);
void scene_link_entry_shutdown(void);
#endif
