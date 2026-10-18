#include "link_entry_receive.h"

void link_apply_received_actor_entry(void)
{
 display_text_select_font(1,3,0);
 display_scene_hide_entry_objects();
 if(event_get_link_slot()==g_link_entry_effect_state.selected) {
  actor_entry_add(g_link_entry_game_state.entries,g_link_received_join.metadata[1],g_link_received_join.metadata[2],g_link_received_join.metadata[3]);
  {
   unsigned char quantity = g_link_entry_effect_state.records[g_link_entry_effect_state.selected].count;
   register int product asm("r3") = g_link_entry_effect_state.multiplier * quantity;
   register int adjustment asm("r1") = g_link_entry_effect_state.records[g_link_entry_effect_state.selected].cost;
   adjustment = product + adjustment;
   g_link_entry_game_state.amount -= adjustment >> 16;
  }
  audio_select_sequence(60);
  {unsigned int linked=g_game_flags&0x20;
   if(!linked) {
    display_text_select_font(3,0,0);
    display_text_number_field_zero(g_link_entry_game_state.amount);
    display_fill_background_constant_rectangle(0,2,1,7,2,linked);
    display_text_draw_line(1,48,14,display_scene_lookup_text(6220),1);
   } else {
    display_text_select_font(3,0,0);
    display_text_number_field_zero(g_link_entry_game_state.amount);
    display_fill_background_constant_rectangle(0,2,6,7,2,0);
    display_text_draw_line(1,48,52,display_scene_lookup_text(6220),1);
   }
  }
 } else if(event_get_link_slot()!=g_link_received_join.identifier)audio_select_sequence(61);
 if(event_get_link_slot()==g_link_received_join.identifier) {
  condition_update_actor(g_link_entry_game_state.entries,g_link_received_join.entry_index,1);
  {
   unsigned char quantity = g_link_entry_effect_state.records[g_link_entry_effect_state.selected].count;
   register int product asm("r3") = g_link_entry_effect_state.multiplier * quantity;
   register int adjustment asm("r1") = g_link_entry_effect_state.records[g_link_entry_effect_state.selected].cost;
   adjustment = product + adjustment;
   g_link_entry_game_state.amount += adjustment >> 16;
  }
  audio_play_animation_cue(5);
  {unsigned int linked=g_game_flags&0x20;
   if(!linked) {
    display_text_select_font(3,0,0);
    display_text_number_field_zero(g_link_entry_game_state.amount);
    display_fill_background_constant_rectangle(0,2,1,7,2,linked);
    display_text_draw_line(1,48,14,display_scene_lookup_text(6220),1);
   } else {
    display_text_select_font(3,0,0);
    display_text_number_field_zero(g_link_entry_game_state.amount);
    display_fill_background_constant_rectangle(0,2,6,7,2,0);
    display_text_draw_line(1,48,52,display_scene_lookup_text(6220),1);
   }
  }
  display_text_draw_all_lines(191,165,64,136,display_scene_lookup_text(227),1);
 } else display_text_draw_all_lines(191,165,64,136,display_scene_lookup_text(225),1);
 display_text_copy_field_zero((const char *)&g_link_received_pairs[g_link_entry_effect_state.selected]);
 display_text_draw_all_lines(71,165,16,136,display_scene_lookup_text(447),1);
}
