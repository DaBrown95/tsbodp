#include "frame_grid_math.h"
unsigned char frame_grid_snap_point_to_corner(void *context,const struct FramePoint *point,struct FramePoint *output) {struct FrameMapRegistration *registration=context;int cell;struct FramePoint coordinates;if(frame_grid_point_to_cell(context,point,(struct FrameActorPackedCell *)&cell)==0) {return 0;}coordinates.x=((unsigned char *)&cell)[0]*registration->cell_size;coordinates.y=((unsigned char *)&cell)[1]*registration->cell_size;frame_grid_coordinates_to_point(registration,&coordinates,output);return 1;}
asm(".align 2,0");
