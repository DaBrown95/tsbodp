#include "scene_catalog_text.h"
#include "scene_catalog_transfer.h"
void scene_catalog_notice(unsigned int input) {
 unsigned short text_id=input;
 unsigned int control=g_scene_catalog_bg1_alt,width;
 display_show_background(1,control);
 display_fill_background(1,0);
 scene_view_load_fixed_resource(1,392,9);
 width=(unsigned int)display_text_measure_width(display_scene_lookup_text(text_id));
 width=((width+7)>>3)+2;
 scene_view_draw_frame((30-width)>>1,5,width,4);
 display_text_set_background_control(control);
 display_text_select_font(3,0,-1);
 display_text_draw_line(401,120,50,display_scene_lookup_text(text_id),1);
 display_text_set_background_control(g_scene_catalog_bg0);
 g_scene_request.unknown_10=3;
 audio_play_animation_cue(3);
}
asm(".align 2,0");
