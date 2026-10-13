#include "scene_primary.h"
void scene_primary_exit(void)
{
 if((g_game_flags&0x20020)==0x20020)transition_fade_black_out_record(0x3f);
 else transition_run_second(0x3f,0);
 g_scene_primary_views.slots[0].saved_direction=g_scene_primary_views.slots[0].object->direction;
 g_scene_primary_views.slots[0].saved_x=g_scene_primary_views.slots[0].object->position.x>>16;
 g_scene_primary_views.slots[0].saved_y=g_scene_primary_views.slots[0].object->position.y>>16;
 scene_stage_080202e0(g_scene_entry_data,g_scene_id);
 if(scene_queued_request_kind()!=5&&scene_queued_request_kind()!=13&&scene_queued_request_kind()!=1&&scene_queued_request_kind()!=20&&scene_queued_request_kind()!=27)scene_stage_08026928();
 else scene_stage_0802697c();
 if(g_game_flags&0x20000)g_game_flags|=0x100000;
 scene_stage_0801eea8();
 if(g_scene_request.mode==0){scene_stage_08041374();display_release_object_list(&g_frame_primary_list);scene_stage_0802eb9c();scene_stage_0803b8c0(g_frame_registration);g_frame_registration=0;g_audio_control.flags&=~8;}
 if(g_scene_request.mode==2)display_reset_tile_allocation();else frame_clear_transient_effects();
 frame_clear_render_effects();frame_release_scene_transient_tiles();frame_configure_deferred_display(0);scene_stage_080117bc();display_reset();set_vblank_callback(irq_default_vblank_callback);
}
