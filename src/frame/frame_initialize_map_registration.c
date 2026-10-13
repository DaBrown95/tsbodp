#include "frame_grid_math.h"
unsigned char frame_initialize_map_registration(struct FrameMapRegistration *registration, unsigned short width,unsigned short height,unsigned char cell_size) {
 struct FramePoint coordinates, point, origin;
 unsigned short columns=(unsigned int)width/cell_size;
 unsigned short rows=(unsigned int)height/cell_size;
 unsigned int extent=columns/2+rows;
 registration->data=0;
 registration->cell_size=cell_size;
 registration->extent=extent;
 registration->span=extent*cell_size;
 registration->origin_x=0;
 registration->origin_y=0;
 coordinates.x=height;
 coordinates.y=0;
 frame_grid_coordinates_to_point(registration,&coordinates,&point);
 origin.x=-point.x;
 origin.y=-point.y;
 registration->origin_x=origin.x;
 registration->origin_y=origin.y+8;
 return 1;
}
asm(".align 2,0");
