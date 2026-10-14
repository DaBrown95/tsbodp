#include "link_endpoint_setup.h"
void link_initialize_endpoint(void)
{
 unsigned int i;
 unsigned int zero;
 g_link_setup_state.first = &g_link_setup_state.queue[0];
 g_link_setup_state.second = &g_link_setup_state.queue[0];
 for (i=0;i<4;i++) {
  g_link_setup_state.first_records[i]=&g_link_setup_state.first_storage[i];
  g_link_setup_state.second_records[i]=&g_link_setup_state.second_storage[i];
 }
 g_link_setup_state.active=0;
 g_link_setup_state.callback=0;
 g_link_setup_state.slot=255;
 g_link_setup_state.identifier=-1;
 g_link_word_0300733c=0;
 g_link_clock_03002178=0;
 g_link_word_0300734c=0;
 g_link_word_03007344=0;
 g_link_word_03007354=0;
 g_link_word_03007348=0;
 g_link_word_03002190=0;
 g_link_peer_count=0;
 g_link_byte_03007340=0;
 g_link_byte_03007338=0;
 g_link_flags=64;
 LINK_REG16(0x0400012a)=0xffff;
 for (i=0;i<4;i++) {
  zero=0;
  resource_bios_swi_0b(&zero,&g_link_received_events[i],0x05000003);
 }
 zero=0;
 resource_bios_swi_0b(&zero,&g_event_record,0x05000003);
 link_set_tick_callback(link_tick_clock);
 g_link_word_03002184=0;
 LINK_REG16(0x04000134)=0;
 LINK_REG16(0x04000128)=0x2000;
 LINK_REG16(0x04000128)|=0x4003;
 link_reset_random_bytes();
 g_link_setup_state.identifier=-1;
 g_link_word_0300218c=-1;
 g_link_recording &= ~1u;
}
