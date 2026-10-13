#include "frame_grid_cells.h"
void frame_grid_clear_terrain(void *context,const void *cell)
{
 struct FrameGridCellProperties *data=(struct FrameGridCellProperties *)frame_grid_cell_data_pointer(context,cell);
 if(data){data->terrain = 0;}
}
asm(".align 2, 0");
