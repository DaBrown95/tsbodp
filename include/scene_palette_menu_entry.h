#ifndef SCENE_PALETTE_MENU_ENTRY_H
#define SCENE_PALETTE_MENU_ENTRY_H

#include "scene_palette_menu.h"
#include "scene_link_menu_actions.h"
#include "display_text_template.h"

extern const struct BackgroundResource g_palette_menu_entry_background2;
extern const struct BackgroundResource g_palette_menu_entry_background1;
extern const struct DisplayTextTemplateEntry g_palette_menu_entry_template[];
void display_set_background_scroll_target(unsigned int, int, int, unsigned int);
void scene_palette_menu_prepare_entry(void);
/* Explicit original object builder; no C coverage is claimed for it. */
void scene_palette_menu_build_entry_objects(void);

#endif
