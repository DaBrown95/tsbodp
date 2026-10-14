#include "scene_catalog_text.h"
void scene_catalog_build(void) {
 display_text_select_font(1,0,0);
 display_fill_background_constant_rectangle(0,4,3,10,2,0);
 display_text_number_field_zero(g_scene_catalog_heading_world.value);
 display_text_draw_line(551,74,24,display_scene_lookup_text(0x184c),1);
}
asm(".align 2,0");
