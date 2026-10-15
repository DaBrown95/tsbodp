#include "frame_collision_response.h"



/* Private matching candidate. The second object's direction must be 0..7.
 * The native out-of-range branch leaves its sample coordinates unwritten;
 * no runtime guarantee of this precondition is claimed here. Geometry inputs
 * and point additions must also remain within the signed-word C domain. */
void frame_resolve_actor_contact(struct FrameObject *object,
                                  struct FrameObject *other)
{
 int first_top,first_left,first_bottom,first_right;
 struct FramePoint position=object->next_position;
 int top,bottom,left,right;
 struct FramePoint first,second,offset;
 int intersecting,second_inside;
 unsigned int direction;
 first_top=(position.y>>16)+object->bound_y0;
 first_bottom=(position.y>>16)+object->bound_y1;
 if(object->render_special<0) {
  first_left=(position.x>>16)-object->bound_x1;
  first_right=(position.x>>16)-object->bound_x0;
 }else{
  first_left=(position.x>>16)+object->bound_x0;
  first_right=(position.x>>16)+object->bound_x1;
 }
 position=other->next_position;
 top=(position.y>>16)+other->bound_y0;
 bottom=(position.y>>16)+other->bound_y1;
 if(other->render_special<0) {
  left=(position.x>>16)-other->bound_x1;
  right=(position.x>>16)-other->bound_x0;
 }else{
  left=(position.x>>16)+other->bound_x0;
  right=(position.x>>16)+other->bound_x1;
 }
 direction=((struct FrameCollisionMotion*)other)->direction;
 switch(direction) {
 case 0:first.x=left;first.y=top;second.x=right;second.y=top;break;
 case 1:first.x=left+((right-left)>>1);first.y=top;second.x=right;second.y=top+((bottom-top)>>1);break;
 case 2:first.x=right;first.y=top;second.x=right;second.y=bottom;break;
 case 3:first.x=left+((right-left)>>1);first.y=bottom;second.x=right;second.y=top+((bottom-top)>>1);break;
 case 4:first.x=left;first.y=bottom;second.x=right;second.y=bottom;break;
 case 5:first.x=left+((right-left)>>1);first.y=bottom;second.x=left;second.y=top+((bottom-top)>>1);break;
 case 6:first.x=left;first.y=top;second.x=left;second.y=bottom;break;
 case 7:first.x=left+((right-left)>>1);first.y=top;second.x=left;second.y=top+((bottom-top)>>1);break;
 }
 intersecting=0;
 if(first.x>=first_left && first.x<=first_right &&
    first.y>=first_top && first.y<=first_bottom)intersecting=1;
 second_inside=0;
 if(second.x>=first_left && second.x<=first_right &&
    second.y>=first_top && second.y<=first_bottom)second_inside=1;
 if(intersecting || second_inside) {
  if(direction&1) {
   if(intersecting)other->next_position.y=other->position.y;
   if(second_inside)other->next_position.x=other->position.x;
  }else{
   offset.x=0;offset.y=0;
   if(intersecting) {
    if(direction==0 || direction==4)offset.x=((struct FrameCollisionMotion*)other)->speed>>3;
    else offset.y=((struct FrameCollisionMotion*)other)->speed>>3;
    frame_add_points(&other->position,&offset,&other->next_position);
   }
   if(second_inside) {
    if(direction==0 || direction==4)offset.x=(-((struct FrameCollisionMotion*)other)->speed)>>3;
    else offset.y=(-((struct FrameCollisionMotion*)other)->speed)>>3;
    frame_add_points(&other->position,&offset,&other->next_position);
   }
   if(intersecting && second_inside)other->next_position=other->position;
  }
 }else{
  intersecting=1;
  if(first_right<left)intersecting=0;
  else if(first_left>right)intersecting=0;
  else if(first_top>bottom)intersecting=0;
  else if(first_bottom<top)intersecting=0;
  if(intersecting==1) {
   other->next_position=other->position;
   other->velocity.y=0;other->velocity.x=0;
   ((struct FrameCollisionContactState*)other)->contact|=1;
  }
 }
}
asm(".align 2,0");
