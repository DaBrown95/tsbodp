#include "frame_terrain_classifier.h"
unsigned int frame_map_terrain_at(struct FramePoint position)
{
 struct FramePoint dimensions;
 register unsigned int y asm("r5")=position.y;register unsigned int x asm("r4")=position.x;unsigned int kind;
 frame_get_map_dimensions(&dimensions);
 if(x>dimensions.x || y>dimensions.y)return 3;
 {unsigned int offset=(g_frame_layer_blocks[(x>>5)+(y>>5)*(dimensions.x>>5)]<<4)+(((x>>3)&3)|((y>>1)&12));kind=g_frame_layer_cells[offset]&63;}
 if(kind-4<=31) {
  union FrameTerrainLine edge=g_frame_movement_contact_lines[kind-4];
  struct FramePoint difference={edge.nibble.x1-edge.nibble.x0,edge.nibble.y1-edge.nibble.y0};
  int local[2];local[0]=(x&7)-edge.nibble.x0;local[1]=(y&7)-edge.nibble.y0;
  if(difference.x*local[1]-local[0]*difference.y<0)return 0;
 }
 return kind;
}
/* Preserve the original zero-filled alignment after the C symbol. */
asm(".align 2, 0");
