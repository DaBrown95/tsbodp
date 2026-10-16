#include "scene_link_status_private.h"
void scene_link_status_initialize(void)
{
 unsigned int index;
 g_link_status_visible_count=0;
 display_set_mode(0);
 display_enable_layers(4096);
 display_load_resource_palette(&g_display_scrolling_palette,0);
 display_show_background(3,g_link_status_control3);
 display_load_background(3,&g_link_status_background3,0,1,0,0);
 display_set_background_velocity(3,-65536,-65536);
 display_show_background(2,g_link_status_control2);
 display_fill_background(2,17);
 display_load_background(2,&g_link_status_background2,18,1,4,1);
 display_show_background(0,g_link_status_control0);
 display_clear_background_map(0);
 display_text_set_background_control(g_link_status_control0);
 display_text_select_font(3,0,0);
 display_text_draw_line(17,120,13,display_scene_lookup_text(6099),1);
 for(index=0;index<4;index++)scene_link_status_create_indicator(index);
 audio_select_sequence(0);
 g_scene_request.scene=6659;
 g_scene_request.parameter=0;
 if(g_link_status_previous_scene==23)g_scene_request.unknown_10=5;
 else g_scene_request.unknown_10=3;
 scene_stage_0803e3a8();
 link_initialize_endpoint();
 g_frame_flags&=~32u;
 g_link_flags&=~32768u;
 set_word_0300217c(9);
 set_word_03002180_bit0(1);
 g_link_status_visible_count=0;
 g_link_status_previous_count=0;
 g_link_status_flicker=0;
 transition_run_first(63,0);
}
asm(".align 2,0");
