#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "view_math.h"
unsigned char frame_actor_direction_available(struct FrameObject *object, unsigned char direction)
{
 struct FramePoint velocity, destination, point;
 struct FrameActorPackedCell cell;
 int current, i;
 unsigned int mask=0xffff;
 frame_make_velocity(&velocity,object->flags,direction,((struct FrameActorObject *)object)->speed);
 destination.x=object->next_position.word.x+velocity.x;
 destination.y=object->next_position.word.y+velocity.y;
 current=direction-1;
 if (current<0) current=direction+7;
 for (i=0; i<3; i++) {
  unsigned int terrain, occupied;
  register unsigned int new_cell asm("r0");
  register unsigned int old_cell asm("r2");
  frame_make_velocity(&velocity,object->flags,current,0x40000);
  frame_add_points(&velocity,&destination,&point);
  point.x>>=16;
  point.y=((short *)&point)[3];
  frame_grid_point_to_cell(g_frame_registration,&point,&cell);
  new_cell=cell.index;
  old_cell=((struct FrameActorPackedCellView *)object)->cell.index;
  if ((new_cell & mask)!=(old_cell & mask)) {
   terrain=frame_grid_terrain(g_frame_registration,(const int *)&cell);
   occupied=frame_grid_occupancy(g_frame_registration,(const int *)&cell);
   if (!(terrain&2) || (occupied&0x3d))
    return 0;
  }
  current++;
  if (current>7) current-=8;
 }
 return 1;
}
asm(".align 2, 0");
