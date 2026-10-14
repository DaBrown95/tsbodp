#include "scene_contact_serial_session.h"
#include "scene_link_menu.h"
#include "save_game_loading.h"
#include "audio_game.h"
#include "heap.h"

void scene_contact_initialize_serial_session(void)
{
 unsigned int control;
 unsigned int slot;
 display_set_mode(0);
 display_enable_layers(4096);
 display_load_resource_palette(&g_scene_contact_serial_initializer_palette,0);
 display_show_background(3,g_scene_contact_serial_initializer_control3);
 display_load_background(3,&g_scene_contact_serial_initializer_background,0,1,0,0);
 display_set_background_velocity(3,-65536,-65536);
 display_show_background(2,g_scene_contact_serial_initializer_control2);
 display_fill_background(2,17);
 display_load_background(2,&g_scene_contact_serial_initializer_first_panel,18,1,4,1);
 display_load_background(2,&g_scene_contact_serial_initializer_second_panel,65,2,0,17);
 control=g_scene_contact_serial_initializer_control0;
 display_show_background(0,control);
 scene_contact_original_disable_background(0);
 display_text_set_background_control(control);
 display_text_select_font(3,0,0);
 display_text_draw_line(17,120,13,display_scene_lookup_text(226),1);
 display_text_draw_line(177,144,144,display_scene_lookup_text(244),0);
 for(slot=0;slot<4;++slot)scene_contact_prepare_serial_slot(slot);
 save_stream_suspend_audio();
 save_stream_read_slot(3);
 save_stream_resume_audio();
 save_stream_validate_slot(3);
 if(g_save_stream_state.valid[3]&&g_save_stream_state.records[3].unknown00)
  save_stream_load_buffer(3);
 g_scene_contact_serial_session.initial00=6659;
 g_scene_contact_serial_session.status04=6659;
 g_scene_contact_serial_session.status06=6659;
 g_scene_contact_serial_session.buffer0c=heap_allocate_zeroed(108);
 g_scene_contact_serial_session.word10=49152;
 transition_run_first(63,0);
 if(!g_scene_request.mode)
  scene_contact_install_serial_irq(scene_contact_dispatch_serial_notice,68,132);
 else {
  g_scene_contact_input_setup.handler=scene_contact_dispatch_serial_notice;
  audio_select_sequence(0);
 }
}
