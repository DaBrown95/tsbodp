#include "frame_option_object.h"

static inline int frame_option_test_flag(unsigned int index)
{
 register union ResourceGameState *world asm("r0")=&g_resource_game_state;
 return (((unsigned char *)world)[0xe5]>>index)&1;
}
struct FrameObject *frame_create_option_resource(unsigned char group,unsigned char entry)
{
 struct FrameOptionPayload *payload=(struct FrameOptionPayload *)resource_get_object_payload(group,entry);
 unsigned char *parameters=&payload->kind;
 switch(parameters[0]) {
 case 0: break;
 case 1:
  if(parameters[2]<=7 && frame_option_test_flag(parameters[2])) return 0;
  break;
 case 2:
  if((unsigned char)condition_is_complete(3,4,0))return 0;
  break;
 }
 return frame_create_option_object(payload->kind,payload->direction,payload->option,payload->x,payload->y);
}
asm(".align 2, 0");
