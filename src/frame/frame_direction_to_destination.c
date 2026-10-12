#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
unsigned char frame_direction_to_destination(struct FramePoint position,struct FramePoint destination,int tolerance)
{
 unsigned char direction;
 if(position.y>destination.y+tolerance) {
  if(position.x>destination.x+tolerance) direction=7;
  else if(position.x<destination.x-tolerance) direction=1;
  else direction=0;
 } else if(position.y<destination.y-tolerance) {
  if(position.x>destination.x+tolerance) direction=5;
  else if(position.x<destination.x-tolerance) direction=3;
  else direction=4;
 } else {
  if(position.x>destination.x+tolerance) direction=6;
  else if(position.x<destination.x-tolerance) direction=2;
  else direction=8;
 }
 return direction;
}
