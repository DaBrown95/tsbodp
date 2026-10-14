#ifndef SCENE_DEFAULT_MENU_H
#define SCENE_DEFAULT_MENU_H

#include "scene_request.h"
#include "scene_link_menu.h"
#include "input.h"
#include "audio_game.h"
#include "frame_random.h"
#include "save_stream.h"
#include "save_world_defaults.h"

/* Observed option bytes; the complete storage capacity is unproven. */
extern unsigned char g_scene_default_menu_options[];
extern const unsigned char g_scene_default_menu_option_defaults[4];
extern unsigned int g_scene_default_menu_cue_handle;
extern struct FrameObject *g_scene_default_menu_selector;
extern struct SceneRequest g_scene_previous_request;
extern unsigned int g_scene_link_menu_selector_word;

struct PaletteRangeConfig;
extern const unsigned int g_scene_default_menu_control0;
extern const unsigned int g_scene_default_menu_control2;
extern const unsigned int g_scene_default_menu_control_detail;
extern const struct BackgroundResource g_scene_default_menu_background2;
extern const struct BackgroundResource g_scene_default_menu_slot_background;
extern const struct BackgroundResource g_scene_default_menu_detail_background;
extern const struct BackgroundResource g_scene_default_menu_palette;
extern const struct BackgroundResource *const
    g_scene_default_menu_text_backgrounds[];
extern const struct BackgroundResource *const
    g_scene_default_menu_slot_text_backgrounds[];
extern const struct PaletteRangeConfig g_scene_default_menu_palette_ranges;

void scene_default_menu_initialize(void), scene_default_menu_step(void);
void scene_default_menu_shutdown(void);
void scene_default_menu_draw_row(unsigned int, unsigned int);
void scene_default_menu_prepare_background(void);
void scene_default_menu_enter_slots(void), scene_default_menu_accept(void);

/* Connected menu and endpoint declarations; numeric scene-stage naming remains provisional. */
void scene_default_menu_change_selection(void);
void link_initialize_endpoint(void);
void scene_stage_0803e3a8(void);

void display_configure_tile_allocation(unsigned char);
void display_configure_background(unsigned int, unsigned int);
unsigned int display_text_selected_bank(void);
const unsigned short *display_load_background_dma(unsigned int,
    const struct BackgroundResource *, unsigned short, unsigned short,
    unsigned int, unsigned int);
void display_enable_background(unsigned int), display_hide_background(unsigned int);
void display_load_palette_ranges(const struct PaletteRangeConfig *);
void transition_fade_black_out_refresh_twice(unsigned short);
void scene_submit_default_request(unsigned int);
unsigned int input_step_vertical_pressed(unsigned int *, unsigned int,
    unsigned int, unsigned char, unsigned char);
void frame_set_position(struct FrameObject *, int, int);

#endif
