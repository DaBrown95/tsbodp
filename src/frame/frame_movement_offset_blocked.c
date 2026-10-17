#include "frame_movement.h"
unsigned char frame_movement_offset_blocked(struct FrameObject *object,struct FramePoint displacement)
{
 unsigned char allowed=1;
 struct FramePoint saved=object->next_position.word;
 struct FrameActorPackedCell cell;
 struct FramePoint position;
 int bounds[4];
 unsigned int contact;
 object->next_position.word.x+=displacement.x;
 object->next_position.word.y+=displacement.y;
 contact=frame_get_movement_probe_bounds(object,bounds);
 if(g_frame_registration) {
  position.x=object->next_position.halves.x_pixel;
  position.y=object->next_position.halves.y_pixel;
  if(!frame_grid_point_to_cell(g_frame_registration,&position,&cell))allowed=0;
  else if(((struct FrameActorPackedCellView *)object)->cell.index!=cell.index) {
   unsigned int occupancy=frame_grid_occupancy(g_frame_registration,(const int *)&cell);
   unsigned int terrain=frame_grid_terrain(g_frame_registration,(const int *)&cell);
   if((object->flags&0x40) && (occupancy&0x3d))allowed=0;
   if((object->flags&0x10000) && !(terrain&2))allowed=0;
  }
 }
 if(frame_movement_is_contact(contact) || !allowed) {
  object->next_position.word=saved;
  return 1;
 }
 ((struct FrameActorContactWork *)object)->contact|=2;
 return 0;
}
asm(".align 2, 0");
