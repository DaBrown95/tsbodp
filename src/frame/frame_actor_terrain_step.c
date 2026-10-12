#include "frame_actor_runtime.h"
#include "view_math.h"
#include "frame_actor_social.h"
static inline struct FramePoint read_point(const struct FramePoint *point){struct FramePoint result;result.x=point->x;result.y=point->y;return result;}
unsigned char frame_actor_terrain_step(struct FrameObject *object,unsigned char direction)
{
 struct FramePoint point;
 frame_make_velocity(&point,object->flags,direction,((struct FrameActorObject *)object)->speed);
 {int x=point.x+object->position.x,y=point.y+object->position.y;point.x=x>>16;point.y=y>>16;}
 switch(direction) {
 case 0: point.y+=object->bound_y0;break;
 case 1: point.x+=object->bound_x1;point.y+=object->bound_y0;break;
 case 2: point.x+=object->bound_x1;break;
 case 3: point.x+=object->bound_x1;point.y+=object->bound_y1;break;
 case 4: point.y+=object->bound_y1;break;
 case 5: point.x-=object->bound_x1;point.y+=object->bound_y1;break;
 case 6: point.x-=object->bound_x1;break;
 case 7: point.x-=object->bound_x1;point.y+=object->bound_y0;break;
 }
 return frame_map_terrain_at(read_point(&point))&0x3f;
}
