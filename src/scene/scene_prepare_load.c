#include "scene_startup.h"

void scene_prepare_load(void) {
 int player;
 g_resource_selected=0;
 switch(g_scene_request.mode){
 case 4:save_world_initialize();break;
 case 5:case 6:save_stream_load_buffer(g_scene_startup_load_options.selection);break;
 case 7:break;
 default:save_world_initialize();break;
 }
 for(player=0;player<g_input_config.player_count;player++)g_scene_startup_players[player].flags=0;
 g_scene_context.flags=0;
 scene_check_initial_time_flags();
}
asm(".align 2,0");
