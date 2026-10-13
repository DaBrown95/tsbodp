#include "frame_movement.h"
unsigned char frame_movement_direction_blocked(struct FrameObject *object,struct FramePoint displacement)
{
 int dot=object->velocity.x*displacement.x+object->velocity.y*displacement.y;
 struct FramePoint offset;
 if(dot>0) {offset.x=displacement.x*0x4000;offset.y=displacement.y*0x4000;}
 else if(dot<0) {offset.x=-(displacement.x*0x4000);offset.y=-(displacement.y*0x4000);}
 else return 1;
 return frame_movement_offset_blocked(object,offset);
}
asm(".align 2, 0");
