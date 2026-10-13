#include "link_entry_receive.h"

void link_show_received_entry_notice(void)
{
 link_stage_080057a0();
 display_text_select_font(1,3,0);
 if(event_get_link_slot()==g_link_entry_offers.selected) {
  display_text_draw_all_lines(71,165,16,136,display_scene_lookup_text(292),1);
  audio_select_sequence(61);
 } else {
  if(event_get_link_slot()!=g_link_received_join.identifier)audio_select_sequence(61);
  display_text_draw_all_lines(71,165,16,136,display_scene_lookup_text(449),1);
 }
 if(event_get_link_slot()==g_link_received_join.identifier)
  display_text_draw_all_lines(191,165,64,136,display_scene_lookup_text(227),1);
 else display_text_draw_all_lines(191,165,64,136,display_scene_lookup_text(225),1);
}
asm(".align 2,0");
