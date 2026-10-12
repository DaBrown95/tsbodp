#include "frame_render.h"
extern unsigned char *g_oam_previous;
int frame_append_oam(FrameU8 index, struct FrameOam *source)
{
 if ((signed char)g_frame_display_channel < 0)
  return -1;
 {
  struct FrameOam *bank = (struct FrameOam *)g_oam_previous;
  struct FrameOam *first = bank + index;
  *first = *source;
  bank += 128;
  bank += index;
  *bank = *source;
  g_frame_display_channel++;
  return 0;
 }
}
asm(".align 2, 0");
