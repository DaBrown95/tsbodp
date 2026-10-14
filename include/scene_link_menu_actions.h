#ifndef SCENE_LINK_MENU_ACTIONS_H
#define SCENE_LINK_MENU_ACTIONS_H

#include "scene_link_menu.h"

struct PaletteRangeConfig;
extern const struct PaletteRangeConfig g_display_menu_palette_ranges;
/* Only the observed full-word selector write is established. */
extern unsigned int g_scene_link_menu_selector_word;
void display_enable_background(unsigned int), display_hide_background(unsigned int);
void display_load_palette_ranges(const struct PaletteRangeConfig *);
unsigned int audio_play_animation_cue(unsigned int);
void scene_submit_default_request(unsigned int);
void frame_set_position(struct FrameObject *, int, int);
unsigned int input_step_local_vertical_pressed(unsigned int *, unsigned int,
    unsigned int, unsigned char, unsigned char);

#endif
