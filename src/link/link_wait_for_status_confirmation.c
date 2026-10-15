#include "link_status_poll_private.h"
void link_wait_for_status_confirmation(void)
{
 unsigned int count=0;
 g_link_flags|=0x20000;
 while(!(g_link_flags&4) || count<20) {
  count++;
  irq_wait_vblank();
 }
 g_link_flags&=~0x20000u;
}
