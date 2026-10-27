#ifndef SCENE_PALETTE_MENU_SELECTOR_H
#define SCENE_PALETTE_MENU_SELECTOR_H

/* Direct selector input, confirmation and redraw handoffs. */
void scene_palette_menu_phase_4(void);
void scene_palette_menu_phase_5(void);
void scene_palette_menu_refresh_selector(unsigned int);
/* Navigation through rows eight to fourteen and group/available transfers. */
void scene_palette_menu_adjust_selection(void);
extern const unsigned short g_palette_menu_selector_colors[];

#endif
