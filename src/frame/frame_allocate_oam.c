#include "frame_oam.h"
unsigned char frame_allocate_oam(void) {
 unsigned char index=0;
 do {
  struct FrameOam *bank=(struct FrameOam *)g_oam_previous;
  bank += index;
  if (bank->display_mode != 2) { index++; continue; }
  {
   frame_enable_oam(index);
   return index;
  }
 } while ((signed char)index >= 0);
 return 255;
}
asm(".align 2, 0");
