#include "frame_actor_target_cells.h"
unsigned int frame_grid_terrain(void *context,const int *cell) {
 unsigned char *data=frame_grid_cell_data_pointer(context,cell);
 if(!data)return 0;
 else return ((struct FrameGridCellProperties*)data)->terrain;
}
asm(".align 2, 0");
