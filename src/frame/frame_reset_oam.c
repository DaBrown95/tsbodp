#include "frame_oam.h"
void frame_reset_oam(void) {
 unsigned int index;
 for(index=0;index<128;index++) {
  struct FrameOam *bank=(struct FrameOam *)g_oam_previous;
  struct FrameOam *first=bank+index;
  *first=g_oam_empty;
  bank += 128;
  bank += index;
  *bank=g_oam_empty;
 }
 FRAME_OAM_DMA3->source=(unsigned int)g_oam_previous;
 FRAME_OAM_DMA3->destination=0x07000000;
 FRAME_OAM_DMA3->control=0x84000100;
 FRAME_OAM_DMA3->control;
 g_frame_display_channel=0;
}
asm(".align 2, 0");
