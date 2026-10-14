#include "scene_scroll_text.h"
void scene_scroll_text_initialize(void){
 unsigned short zero;const char *text;
 audio_select_sequence(9);{unsigned short *fill=&zero;*fill=0;resource_bios_swi_0b(fill,&g_scene_scroll_text_state,0x01000008);}
 g_scene_scroll_text_state.x=162;g_scene_scroll_text_state.y=160;g_scene_request.parameter=6292;
 display_set_mode(0);display_enable_layers(4096);display_show_background(3,g_scene_scroll_control3);
 display_load_background(3,&g_scene_scroll_background3,0,0,0,0);
 display_load_background_dma(3,g_scene_scroll_text_backgrounds[display_text_selected_bank()],257,0,1,1);
 display_show_background(2,g_scene_scroll_control2);display_load_background_dma(2,&g_scene_scroll_background2,27,0,0,0);
 display_load_palette((const unsigned short *)((const unsigned char *)&g_scene_scroll_background2+2),0,16);
 display_load_palette_alternate(g_scene_scroll_palette,0,16);display_text_select_font(1,3,0);
 transition_run_first(63,0);transition_configure_alpha(0,40);transition_set_alpha(8,8);
 g_display_scene_frame_objects[0]=frame_create_scene_object(174,235,1,1);
 display_text_select_font(3,0,0);text=display_scene_lookup_text(23);
 g_display_scene_frame_objects[1]=display_scene_create_label(175,&text);
 transition_object_set_state((struct TransitionObject *)g_display_scene_frame_objects[1],14);frame_set_variant_state(g_display_scene_frame_objects[1],58);
}

asm(".align 2,0");
