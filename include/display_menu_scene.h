#ifndef DISPLAY_MENU_SCENE_H
#define DISPLAY_MENU_SCENE_H
#include "display_menu.h"
#include "save_world_view_resources.h"

struct BackgroundResource;
struct PaletteRangeConfig;
extern const unsigned int g_display_menu_control0, g_display_menu_control1;
extern const unsigned int g_display_menu_control2, g_display_menu_control3;
extern const unsigned short g_display_menu_palette_data[];
extern const struct BackgroundResource g_display_menu_palette_resource;
extern const struct BackgroundResource g_display_menu_panel_resource;
extern const struct PaletteRangeConfig g_display_menu_palette_ranges;
/* Unconverted dependencies; stage roles follow this caller's observed uses. */
void display_menu_clear_effects(void);
void display_menu_prepare_relation(void *, unsigned int);
int display_menu_read_relation(void *, unsigned int);
void display_menu_load_relation_resource(void);
void display_menu_prepare_footer(void);
void display_menu_prepare_primary(void);
void display_menu_prepare_secondary(void);
void display_menu_prepare_tertiary(void);
void transition_run_first(unsigned short, unsigned int);

#endif
