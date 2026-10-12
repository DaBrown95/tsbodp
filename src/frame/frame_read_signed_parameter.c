#include "frame_actor_needs.h"
#include "frame_actor_social.h"
int frame_read_signed_parameter(const void *state,unsigned int index)
{
 unsigned int address=(unsigned int)state;
 address+=index*4;
 return *((signed char*)address+3);
}
