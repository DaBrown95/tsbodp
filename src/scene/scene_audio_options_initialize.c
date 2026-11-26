#include "frame.h"
#include "scene_audio_options.h"
void scene_audio_options_initialize(void) {
 unsigned char row;
 g_scene_request.parameter=0;
 if(g_scene_previous_request.unknown_00==5||g_scene_previous_request.unknown_00==11)g_scene_audio_option_return_kind=g_scene_previous_request.unknown_00;
 else g_scene_audio_option_return_kind=g_scene_previous_request.scene;
 g_scene_audio_option_levels[0]=display_bios_div(g_audio_game_options.sequences_volume,25);
 g_scene_audio_option_levels[1]=display_bios_div(g_audio_game_options.samples_volume,12);
 if(g_scene_previous_request.unknown_00!=13)g_scene_audio_option_sequence=g_audio_control.sequence_id;
 audio_select_sequence(g_scene_audio_option_sequence);
 display_set_mode(0);display_enable_layers(0x1000);
 display_show_background(1,g_scene_audio_option_control1);display_fill_background(1,0);
 display_load_background(1,&g_scene_audio_option_background1,1,0,0,0);
 display_load_background_dma(1,g_scene_audio_option_text_backgrounds[display_text_selected_bank()],287,0,11,1);
 {unsigned int control=g_scene_audio_option_control0;display_show_background(0,control);display_load_resource_palette(&g_display_menu_palette_resource,0);display_show_background(2,g_scene_audio_option_control2);display_load_background_dma(2,&g_scene_audio_option_background2,455,0,0,0);display_text_set_background_control(control);}
 display_fill_background(0,0);display_load_palette_ranges(&g_display_menu_palette_ranges);
 g_display_scene_frame_objects[0]=frame_create_scene_object(168,313,1,1);
 g_display_scene_frame_objects[1]=frame_create_scene_object(169,270,2,1);
 if(!g_scene_audio_option_levels[1])g_display_scene_frame_objects[1]->flags&=~1U;
 g_display_scene_frame_objects[2]=frame_create_scene_object(170,271,2,1);
 if(g_scene_audio_option_levels[1]==10)g_display_scene_frame_objects[2]->flags&=~1U;
 g_display_scene_frame_objects[3]=frame_create_scene_object(171,270,2,1);
 if(!g_scene_audio_option_levels[0])g_display_scene_frame_objects[3]->flags&=~1U;
 g_display_scene_frame_objects[4]=frame_create_scene_object(172,271,2,1);
 if(g_scene_audio_option_levels[0]==10)g_display_scene_frame_objects[4]->flags&=~1U;
 for(row=0;row<=3;row++)scene_audio_options_draw_row(row);
 transition_run_first(63,0);
}
asm(".align 2,0");
