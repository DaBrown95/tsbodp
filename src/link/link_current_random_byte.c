#include "link_endpoint_setup.h"
unsigned int link_current_random_byte(void)
{ return g_frame_random_last_byte; }
asm(".align 2,0");
