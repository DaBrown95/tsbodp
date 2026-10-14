#include "scene_palette_menu_selection_transition.h"
void scene_palette_menu_prepare_selected_exit(void) {
 display_fill_background(1,0);
 display_load_background(1,&g_palette_menu_selected_exit_background,18,3,3,5);
 display_set_background_scroll_target(1,0,-160*65536,1);
 display_set_background_scroll_target(0,0,-160*65536,1);
}
asm(".align 2,0");
