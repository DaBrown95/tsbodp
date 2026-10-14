#include "scene_palette_menu.h"
void scene_palette_menu_initialize(void){
 unsigned int i;unsigned int control;
 g_scene_palette_menu_owner=heap_allocate_zeroed(308);g_scene_palette_menu_owner->initial_word=25;
 g_scene_request.scene=0;g_scene_request.unknown_10=0;g_scene_request.unknown_14=30;
 for(i=0;i<=14;i++)g_frame_actor_palette_menu_choices[i]=0;
 g_scene_palette_menu_owner->parameters=g_scene_palette_menu_parameter_base;
 display_set_mode(0);display_enable_layers(4096);
 control=g_scene_palette_menu_control0;display_configure_background(0,control);display_fill_background(0,0);
 display_show_background(3,g_scene_palette_menu_control3);display_configure_background(2,g_scene_palette_menu_control2);display_fill_background(2,0);
 display_configure_background(1,g_scene_palette_menu_control1);display_fill_background(1,0);
 display_text_set_background_control(control);display_load_palette_alternate(g_scene_palette_menu_palette,0,16);
 heap_clear(g_frame_actor_palette_menu_exit_objects,0,32);g_frame_actor_palette_menu_exit_count=0;g_frame_actor_palette_menu_text_flag=0;
 g_scene_request.unknown_14=31;display_load_background(3,&g_scene_palette_menu_background3,1,1,0,0);
 display_set_background_velocity(3,65536,65536);audio_select_sequence(1);transition_run_first(63,0);
}
asm(".align 2,0");
