#include "link_serial_handshake.h"
static inline void restart_if_ready(void)
{
 if(!(HANDSHAKE_CONTROL&4)) {
  HANDSHAKE_CONTROL|=0x80;
  HANDSHAKE_TIMER=0xc0;
 }
}
static inline void install_transfer_callback(void)
{
 g_link_setup_state.callback=link_serial_timeout;
 g_link_last_serial_vblank=g_irq_context->vblank_count;
 g_irq_table[0]=(unsigned int)link_serial_interrupt;
 g_link_setup_state.identifier=-1;
 link_reset_random_bytes();
 g_link_flags|=4;
 g_link_flags&=~0x20000u;
}
void link_serial_handshake(void)
{
 int peer,ready;
 unsigned int received;
 g_link_word_0300218c=0;
 g_link_byte_03007338=0;
 g_link_word_03007350=0;
 if(HANDSHAKE_CONTROL&0xc0)return;
 {
  unsigned short external_clock=HANDSHAKE_CONTROL&4;
  if(!external_clock)HANDSHAKE_TIMER=external_clock;
 }
 for(peer=3;peer>=0;--peer) {
  received=HANDSHAKE_RECEIVE(peer);
  if(received==0xbeef||received==0xc0de||received==0xbabe||received==0xdead) {
   g_link_word_0300218c=5;
   if(!(HANDSHAKE_CONTROL&4))restart_if_ready();
   return;
  }
  if(received==0xfeed||received==0xb0ca) {
   ++g_link_word_0300218c;
   g_link_byte_03007338|=1u<<peer;
   if(received==0xb0ca)g_link_flags|=0x20000;
  }
 }
 if(g_link_word_0300218c)g_link_setup_state.slot=(HANDSHAKE_CONTROL>>4)&3;
 if(g_link_flags&0x20000) {
  if((signed char)g_link_setup_state.slot==0) {
   ready=1;
   for(peer=(int)g_link_setup_state.active-1;peer>0;--peer) {
    if(HANDSHAKE_RECEIVE(peer)!=0xb0ca){ready=0;break;}
   }
   if(ready) {
    install_transfer_callback();
    LINK_REG16(0x0400010c)=0xc352;
    link_start_connection();
    return;
   }
   HANDSHAKE_SEND=0xb0ca;
  }else {
   unsigned short reply=HANDSHAKE_RECEIVE(0);
   if(reply==0xb0ca) {
    HANDSHAKE_SEND=reply;
    install_transfer_callback();
    LINK_REG16(0x0400010c)=0xc352;
    link_start_connection();
    return;
   }
   HANDSHAKE_SEND=0xfeed;
  }
 }else {
  g_link_setup_state.active=g_link_word_0300218c;
  HANDSHAKE_SEND=0xfeed;
 }
 restart_if_ready();
}
