#include "frame_grid_math.h"
unsigned char frame_grid_cell_corner(void *context,const int *cell,struct FramePoint *point){struct FrameMapRegistration *registration=context;struct FramePoint coordinates;coordinates.x=((const unsigned char *)cell)[0]*registration->cell_size;coordinates.y=((const unsigned char *)cell)[1]*registration->cell_size;return frame_grid_coordinates_to_point(registration,&coordinates,point);}
asm(".align 2,0");
