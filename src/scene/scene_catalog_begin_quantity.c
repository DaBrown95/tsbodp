#include "scene_catalog_text.h"
void scene_catalog_begin_quantity(void) {
 unsigned int quantity=g_scene_catalog_world.quantities[g_scene_request.scene];
 unsigned int style,tile,width;
 if(!quantity) {
  audio_play_animation_cue(3);
  return;
 }
 g_scene_request.unknown_10=2;
 style=1;
 g_scene_request.parameter=style;
 display_text_select_font(3,0,-1);
 scene_view_load_fixed_resource(1,392,9);
 width=(unsigned int)display_text_measure_width(display_scene_lookup_text(439));
 width=((width+7)>>3)+2;
 scene_view_draw_frame((30-width)>>1,5,width,8);
 display_text_set_background_control(g_scene_catalog_bg1_alt);
 tile=401;
 display_text_number_field_zero(quantity);
 tile=display_text_draw_line(tile,120,48,display_scene_lookup_text(438),style);
 display_text_draw_line(tile,120,60,display_scene_lookup_text(439),style);
 scene_catalog_quantity();
 audio_play_animation_cue(1);
}
asm(".align 2,0");
