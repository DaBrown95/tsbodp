#include "frame_map.h"
struct FrameMapDma { unsigned int source, destination, control; };
#define MAP_DMA0 ((volatile struct FrameMapDma *)0x040000B0)
void frame_transfer_map_tiles(unsigned int view) {
 unsigned int i;
 for(i=0;i<2;i++) {
  struct FrameMapRecord *record=&g_frame_map_records[i];
  register const unsigned char *layout asm("r0")=(const unsigned char *)record->source;
  if(layout) {
   unsigned int row;
   int x=(record->origins[(unsigned char)view].x/8)&3;
   int y=(record->origins[(unsigned char)view].y/8)&3;
   unsigned int offset=x+((y | (y<<2))<<3);
   const unsigned short *source=(const unsigned short *)(offset*2+(unsigned int)record->staging);
   register unsigned int tile_offset asm("r2")=layout[1];
   unsigned char *destination=(unsigned char *)(0x06000000+((tile_offset&31)<<11));
   for(row=22;row;row--) {
    MAP_DMA0->source=(unsigned int)source;
    MAP_DMA0->destination=(unsigned int)destination;
    MAP_DMA0->control=0x8000001F;
    MAP_DMA0->control;
    source+=40;
    destination+=64;
   }
  }
 }
}
