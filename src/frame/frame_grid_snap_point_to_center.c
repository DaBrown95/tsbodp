#include "frame_grid_math.h"
unsigned char frame_grid_snap_point_to_center(void *context,const struct FramePoint *point,struct FramePoint *output) {int cell;if(frame_grid_point_to_cell(context,point,(struct FrameActorPackedCell *)&cell) && frame_grid_cell_to_point(context,&cell,output))return 1;return 0;}
asm(".align 2,0");
