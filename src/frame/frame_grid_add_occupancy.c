#include "frame_grid_cells.h"
void frame_grid_add_occupancy(void *context,const void *cell,unsigned int mask)
{
 struct FrameGridCellProperties *data=(struct FrameGridCellProperties *)frame_grid_cell_data_pointer(context,cell);
 if(data){data->occupied |= mask;}
}
asm(".align 2, 0");
