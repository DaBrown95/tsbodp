#include "frame_map_scene.h"
#include "frame_actor_target_cells.h"

unsigned char *frame_grid_cell_data_pointer(void *base, const int *cell)
{
 register struct FrameMapRegistration *context asm("r2")=base;
 unsigned int x=((const unsigned char *)cell)[0];
 unsigned int extent=context->extent;
 unsigned int y;

 if(x>=extent || (y=((const unsigned char *)cell)[1])>=extent)return 0;
 else return (unsigned char *)context->data+y*context->extent+x;
}
