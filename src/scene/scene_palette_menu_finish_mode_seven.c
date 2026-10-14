#include "scene_palette_menu_selection_transition.h"
void scene_palette_menu_finish_mode_seven(void) {
 display_fill_background(2,18);
 display_load_background(2,&g_palette_menu_mode7_background2,18,2,0,0);
 display_set_background_position(2,0,-100*65536);
 display_load_background(1,&g_palette_menu_mode7_background1,44,3,0,0);
 display_load_palette(g_frame_actor_palette_menu_entry_palette,64,16);
 display_set_background_scroll_target(2,0,100*65536,1);
 display_set_background_scroll_target(1,0,-160*65536,1);
 display_set_background_scroll_target(0,0,-160*65536,1);
}
asm(".align 2,0");
