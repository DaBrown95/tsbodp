#include "resource_builders.h"
#include "frame_grid_math.h"
void resource_object_before_step(struct FrameObject *frame) {
 struct FramePoint position;
 if(frame->flags&0x40000) {
  position.x=frame->position.x>>16; position.y=frame->position.y>>16;
  resource_project_point(g_frame_registration,&position,&frame->spatial.bounds.lower);
  frame->spatial.bounds.upper=frame->spatial.bounds.lower;
 }else{
  frame->spatial.bounds.lower.x=0;frame->spatial.bounds.lower.y=frame->position.y>>16;
  frame->spatial.bounds.upper.x=0;frame->spatial.bounds.upper.y=frame->position.y>>16;
 }
}
asm(".align 2, 0");
