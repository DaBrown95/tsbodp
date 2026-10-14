#ifndef SCENE_PALETTE_MENU_INPUT_H
#define SCENE_PALETTE_MENU_INPUT_H

#include "scene_palette_menu_entry.h"
#include "display_text_helpers.h"
#include "display_text_slots.h"
#include "input.h"

/* Four-byte records; only the first and last entry bytes are interpreted. */
struct ScenePaletteMenuEntryRange {
    unsigned char first, last, unknown_02[2];
};
extern const struct ScenePaletteMenuEntryRange g_palette_menu_entry_ranges[];
/* Observed bank/row/entry strides are 208, 52 and 4 bytes; capacity is unknown. */
extern const unsigned int g_palette_menu_character_ids[][4][13];
extern const unsigned short g_palette_menu_cursor_x[];
extern const unsigned char g_palette_menu_cursor_y[];
extern const struct DisplayTextTemplateEntry g_palette_menu_upper_template[];

void scene_palette_menu_phase_1(void);
void scene_palette_menu_refresh_cursor(void);
void scene_palette_menu_refresh_character_bank(void);
void scene_palette_menu_build_entry_objects(void);

#endif
