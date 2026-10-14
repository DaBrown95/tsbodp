#ifndef SCENE_PALETTE_MENU_SELECTION_TRANSITION_H
#define SCENE_PALETTE_MENU_SELECTION_TRANSITION_H

#include "scene_palette_menu_entry.h"
#include "scene_palette_menu_selector.h"

void scene_palette_menu_phase_6(void);
void scene_palette_menu_phase_8(void);
void scene_palette_menu_phase_9(void);
void scene_palette_menu_phase_10(void);
struct FrameObject *scene_palette_menu_create_selection_object(unsigned int,
    unsigned int, unsigned int);
void scene_palette_menu_finish_mode_seven(void);
void scene_palette_menu_prepare_selected_exit(void);

/* Original bodies retain their observed no-argument, effect-only handoffs. */
void scene_palette_menu_build_selection_objects(void);
void scene_palette_menu_release_selection_objects(void);
void display_set_background_position(unsigned int, int, int);
void resource_submit_scene(unsigned int, unsigned int, unsigned int);
extern struct FrameVariantResource g_palette_menu_selection_animation;
extern const struct BackgroundResource g_palette_menu_mode7_background2;
extern const struct BackgroundResource g_palette_menu_mode7_background1;
extern const struct BackgroundResource g_palette_menu_selected_exit_background;

#endif
