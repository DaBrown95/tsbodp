#include "resource_builders.h"
extern void *g_resource_projection_context;
extern void resource_project_point(void *,const struct FramePoint *,struct FramePoint *);
void resource_object_before_step(struct FrameObject *frame) {
 struct FramePoint position;
 if(frame->flags&0x40000) {
  position.x=frame->position.x>>16; position.y=frame->position.y>>16;
  resource_project_point(g_resource_projection_context,&position,&frame->spatial.bounds.lower);
  frame->spatial.bounds.upper=frame->spatial.bounds.lower;
 }else{
  frame->spatial.bounds.lower.x=0;frame->spatial.bounds.lower.y=frame->position.y>>16;
  frame->spatial.bounds.upper.x=0;frame->spatial.bounds.upper.y=frame->position.y>>16;
 }
}
asm(".align 2, 0");
