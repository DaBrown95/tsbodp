#include "frame_grid_math.h"
unsigned char frame_grid_cell_extents(void *context,const int *cell,struct FramePoint *first,struct FramePoint *last) {
 struct FrameMapRegistration *registration=context;
 const unsigned char *index=(const unsigned char *)cell;
 if(first) {first->x=index[0]*registration->cell_size;first->y=index[1]*registration->cell_size+registration->cell_size-1;}
 if(last) {last->x=index[0]*registration->cell_size+registration->cell_size-1;last->y=index[1]*registration->cell_size;}
 return 1;
}
asm(".align 2,0");
