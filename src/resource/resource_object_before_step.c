#include "resource_builders.h"
struct ResourceProjectedObject {
 unsigned char unknown00[12]; unsigned int flags;
 unsigned char unknown10[8]; unsigned short x_fraction; short x; unsigned short y_fraction; short y;
 unsigned char unknown20[124]; int current_x,current_y,previous_x,previous_y;
};
extern void *g_resource_projection_context;
extern void resource_project_point(void *,const struct FramePoint *,struct FramePoint *);
void resource_object_before_step(struct FrameObject *frame) {
 struct FramePoint position;
 if(((struct ResourceProjectedObject *)frame)->flags&0x40000) {
  position.x=((struct ResourceProjectedObject *)frame)->x; position.y=((struct ResourceProjectedObject *)frame)->y;
  resource_project_point(g_resource_projection_context,&position,(struct FramePoint *)&((struct ResourceProjectedObject *)frame)->current_x);
  *(struct FramePoint *)&((struct ResourceProjectedObject *)frame)->previous_x=*(struct FramePoint *)&((struct ResourceProjectedObject *)frame)->current_x;
 }else{
  ((struct ResourceProjectedObject *)frame)->current_x=0;((struct ResourceProjectedObject *)frame)->current_y=((struct ResourceProjectedObject *)frame)->y;
  ((struct ResourceProjectedObject *)frame)->previous_x=0;((struct ResourceProjectedObject *)frame)->previous_y=((struct ResourceProjectedObject *)frame)->y;
 }
}
asm(".align 2, 0");
