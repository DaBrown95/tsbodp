#include "frame_movement.h"
unsigned int frame_get_movement_probe_bounds(struct FrameObject *object,int *bounds)
{
 struct FramePoint position=object->next_position;
 unsigned int heading=((struct FrameMovementDirection *)object)->direction;
 const int *offsets;
 unsigned int mask,direction;
 register unsigned int contact asm("r1");
 int integer_x,integer_y;
 if(frame_object_has_flags(object,0x8000)) {integer_x=position.x>>16;offsets=g_frame_movement_large_bounds;}
 else {integer_x=position.x>>16;offsets=g_frame_movement_small_bounds;}
 bounds[0]=integer_x+offsets[0];
 integer_x+=offsets[1];bounds[1]=integer_x;
 integer_y=(position.y>>16);bounds[2]=integer_y+offsets[2];
 integer_y+=offsets[3];bounds[3]=integer_y;
 if(object->flags&0x20000000) {mask=3;direction=heading>>1;}
 else {mask=1;direction=heading;}
 if(((struct FrameMovementDirection *)object)->direction&mask) {
  direction&=0xfe;
  contact=frame_probe_movement_edge(direction,bounds);
  if(!frame_movement_is_contact(contact))contact=frame_probe_movement_edge((direction+2)&7,bounds);
 } else contact=frame_probe_movement_edge(direction,bounds);
 contact=frame_forward_movement_contact(object,contact);return contact;
}
asm(".align 2, 0");
