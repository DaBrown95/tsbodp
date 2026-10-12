#include "frame_actor_runtime.h"
#include "frame_actor_state.h"

struct FramePoint resource_read_group_point(unsigned char group, unsigned char index)
{
 unsigned char *data = g_actor_point_group_data;
 register unsigned int group_offset asm("r1") = group * 2;
 register unsigned int address asm("r3") = (unsigned int)data + 2;
 struct FrameActorGroupPoint *record;
 struct FramePoint point;
 address += group_offset;
 record = (void *)(data + *(unsigned short *)address + 4 + index * 8);
 point.x = record->x;
 point.y = record->y;
 return point;
}
asm(".align 2, 0");
