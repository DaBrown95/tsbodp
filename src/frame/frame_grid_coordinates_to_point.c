#include "frame_grid_math.h"
unsigned char frame_grid_coordinates_to_point(struct FrameMapRegistration *registration,const struct FramePoint *coordinates,struct FramePoint *point) {
 if(coordinates->x<0 || coordinates->x>=(int)registration->span || coordinates->y<0 || coordinates->y>=(int)registration->span)return 0;
 point->x=registration->origin_x+coordinates->x+coordinates->y;
 point->y=registration->origin_y-coordinates->x/2+coordinates->y/2+8;
 return 1;
}
asm(".align 2,0");
