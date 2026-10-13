#include "frame_grid_math.h"
unsigned char frame_grid_cell_to_point(void *context,const int *cell,struct FramePoint *point) {
 struct FrameMapRegistration *registration=context;
 const unsigned char *index=(const unsigned char *)cell;
 struct FramePoint coordinates;
 if(index[0]>=registration->extent || index[1]>=registration->extent)return 0;
 coordinates.x=index[0]*registration->cell_size+registration->cell_size/2;
 coordinates.y=index[1]*registration->cell_size+registration->cell_size/2;
 frame_grid_project_coordinates(registration,&coordinates,point);
 return 1;
}
asm(".align 2,0");
