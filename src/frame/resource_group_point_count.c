#include "frame_actor_runtime.h"
#include "frame_actor_state.h"

unsigned char resource_group_point_count(unsigned char group)
{
 unsigned char *data = g_actor_point_group_data;
 register unsigned int group_offset asm("r0") = group * 2;
 register unsigned int address asm("r1") = (unsigned int)data + 2;
 address += group_offset;
 return data[*(unsigned short *)address];
}
asm(".align 2, 0");
