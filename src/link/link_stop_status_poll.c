#include "link_status_shutdown.h"

void link_stop_status_poll(void)
{
 if (!(LINK_REG16(0x04000128) & 4))
  LINK_REG16(0x04000200) &= 0xffbf;
 LINK_REG16(0x04000200) &= 0xff7f;
 LINK_REG16(0x0400012a) = 0xffff;
 g_link_setup_state.active = 0;
 g_link_setup_state.slot = 0xff;
}
