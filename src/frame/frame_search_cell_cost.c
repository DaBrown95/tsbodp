#include "frame_search.h"
unsigned int frame_search_cell_cost(const int *cell)
{
 unsigned int occupancy=frame_grid_occupancy(g_frame_grid_search.context,cell);
 unsigned int terrain=frame_grid_terrain(g_frame_grid_search.context,cell);
 unsigned int result;
 if(occupancy&13)goto blocked;
 if(occupancy&16)goto blocked;
 if(terrain&2)goto allowed;
 blocked:result=100;goto done;
 allowed:result=1;
 done:return result;
}
