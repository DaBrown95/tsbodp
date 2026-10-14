#include "frame.h"
#include "scene_catalog_paging.h"
void scene_catalog_refresh_quantities(void){
 unsigned int tile,i;
 unsigned char *quantities;
 display_text_select_font(1,0,0);
 tile=571;
 display_fill_background_constant_rectangle(0,0,8,15,1,0);
 for(i=0,quantities=g_scene_catalog_quantities;i<=4;i++) {
  unsigned int address=i;
  address+=(unsigned int)quantities;
  display_text_number_field_zero(*(const unsigned char *)address);
  tile=display_text_draw_line(tile,g_scene_catalog_caption_positions[i].x,g_scene_catalog_caption_positions[i].y,display_scene_lookup_text(0x184e),1);
 }
}
asm(".align 2,0");
