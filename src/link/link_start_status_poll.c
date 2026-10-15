#include "link_status_poll_private.h"
unsigned int link_start_status_poll(unsigned int count)
{
 g_link_word_03002190=count;
 if(g_link_flags&0x10004)return 5;
 LINK_REG16(0x0400012a)=0xffff;
 while(!(LINK_REG16(0x04000128)&8) || (LINK_REG16(0x04000128)&0x80)) {
  if(g_link_setup_state.callback && (unsigned char)g_link_setup_state.callback()==0)return 7;
 }
 LINK_REG16(0x0400012a)=0xfeed;
 if(!(LINK_REG16(0x04000128)&4)) {
  g_irq_table[0]=(unsigned int)link_handshake_irq_original;
  LINK_REG16(0x04000200)|=0x40;
  LINK_REG16(0x0400010c)=0xc352;
  if(!(LINK_REG16(0x04000128)&4)) {
   LINK_REG16(0x04000128)|=0x80;
   LINK_REG16(0x0400010e)=0xc0;
  }
 } else {
  g_irq_table[0]=(unsigned int)link_handshake_irq_original;
  LINK_REG16(0x04000200)|=0x80;
 }
 irq_wait_vblank();
 return link_read_status_original();
}
