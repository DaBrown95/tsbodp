#include "frame_actor_needs.h"
#include "frame_actor_social.h"
unsigned char frame_actor_need_value(struct FrameActorNeedState *state,unsigned int index)
{
 unsigned int address=(unsigned int)state;
 address+=index*4;
 return *((unsigned char*)address+3);
}
