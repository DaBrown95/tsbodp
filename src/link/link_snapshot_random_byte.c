#include "link_endpoint_setup.h"
void link_snapshot_random_byte(void)
{ g_link_byte_030072fc=g_frame_random_last_byte; }
asm(".align 2,0");
