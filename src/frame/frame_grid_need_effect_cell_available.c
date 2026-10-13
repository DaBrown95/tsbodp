#include "frame_need_effect_placement.h"
#include "frame_actor_target_cells.h"

unsigned char frame_grid_need_effect_cell_available(void *context,
 const struct FrameActorPackedCell *cell, unsigned int action, unsigned char linked)
{
 unsigned int occupied, terrain, available, mask;
 register unsigned int restricted asm("r2");
 unsigned char *data = frame_grid_cell_data_pointer(context, (const int *)cell);

 if (data) occupied = ((struct FrameGridCellProperties *)data)->occupied;
 else occupied = 0;
 data = frame_grid_cell_data_pointer(context, (const int *)cell);
 if (data) terrain = ((struct FrameGridCellProperties *)data)->terrain;
 else terrain = 0;
 if (action == 4) return 1;
 if (!(terrain & 1) && !linked) return 0;
 restricted = 0;
 if (terrain == 1) restricted = 1;
 available = 1;

 switch (action) {
 case 1:
  mask = 61;
 blocked_test:
  if (occupied & mask) goto unavailable;
  else goto unrestricted;
  break;
 case 3:
  mask = 21;
  goto blocked_test;
 case 2:
  if ((occupied & 4) || linked) {
   unrestricted:
   if (restricted == 1) available = 0;
  } else available = 0;
  break;
 case 5:
  if (occupied & 61) available = 0;
  else if (!restricted && !linked) available = 0;
  break;
 case 0:
  break;
 default:
  goto unavailable;
 }
 goto done;
 unavailable:
 available = 0;
 done:
 return available;
}
