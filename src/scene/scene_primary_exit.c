#include "scene_primary.h"
void scene_primary_exit(void)
{
 if((g_game_flags&0x20020)==0x20020)transition_fade_black_out_record(0x3f);
 else transition_run_second(0x3f,0);
 g_scene_primary_views.slots[0].saved_direction=g_scene_primary_views.slots[0].object->direction;
 g_scene_primary_views.slots[0].saved_x=g_scene_primary_views.slots[0].object->position.x>>16;
 g_scene_primary_views.slots[0].saved_y=g_scene_primary_views.slots[0].object->position.y>>16;
 scene_save_need_effect_collection(g_scene_entry_data,g_scene_id);
 if(scene_queued_request_kind()!=5&&scene_queued_request_kind()!=13&&scene_queued_request_kind()!=1&&scene_queued_request_kind()!=20&&scene_queued_request_kind()!=27)scene_retain_display();
 else scene_release_display();
 if(g_game_flags&0x20000)g_game_flags|=0x100000;
 save_world_clear_row_objects();
 if(g_scene_request.mode==0){scene_stage_08041374();display_release_object_list(&g_frame_primary_list);frame_clear_need_effect_states();frame_destroy_map_registration(g_frame_registration);g_frame_registration=0;g_audio_control.flags&=~8;}
 if(g_scene_request.mode==2)display_reset_tile_allocation();else frame_clear_transient_effects();
 frame_clear_render_effects();frame_release_scene_transient_tiles();frame_configure_deferred_display(0);display_reset_palette_jobs();display_reset();set_vblank_callback(irq_default_vblank_callback);
}
