#include "frame_grid_math.h"

unsigned char frame_grid_project_effect_point(struct FrameMapRegistration *registration,
 const struct FramePoint *point, unsigned int direction, struct FramePoint *output)
{
 struct FrameActorPackedCell cell;
 struct FramePoint coordinates;
 if(!frame_grid_point_to_cell(registration,point,&cell))return 0;
 if(direction<=4) {
  coordinates.x=((unsigned char *)&cell)[0]*registration->cell_size;
  coordinates.y=((unsigned char *)&cell)[1]*registration->cell_size;
 } else {
  int cell_x=((unsigned char *)&cell)[0];
  int cell_size=registration->cell_size;
  { int product; product=cell_x*cell_size; product--; coordinates.x=product+cell_size; }
  { int product; product=((unsigned char *)&cell)[1]*cell_size; product--; coordinates.y=product+cell_size; }
 }
 if(frame_grid_coordinates_to_point(registration,&coordinates,output)==1)return 1;
 return 0;
}
asm(".align 2,0");
