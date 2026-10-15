#include "link_serial_handshake.h"
unsigned int link_serial_timeout(void)
{
 if((int)(g_irq_context->vblank_count-g_link_last_serial_vblank)>300)return 1;
 return 0;
}
asm(".align 2,0");
