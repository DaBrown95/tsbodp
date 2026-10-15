#include "transition_mosaic.h"

void transition_mosaic_lightening_refresh(unsigned short targets)
{
 short horizontal = 16;
 short vertical = 16;
 volatile unsigned short display;
 struct FrameObject *object;

 REG16(0x04000050) = targets | 0xC0;
 display = REG16(0x04000000) & 0xFFF8;
 if (display & 0x0100) REG16(0x04000008) |= 0x40;
 if (display & 0x0200) REG16(0x0400000A) |= 0x40;
 if (display & 0x0400) REG16(0x0400000C) |= 0x40;
 if (display & 0x0800) REG16(0x0400000E) |= 0x40;
 if (display & 0x1000) {
  object = g_frame_primary_list.first;
  while (object) {
   unsigned char *flags = (unsigned char *)object + 0xD1;
   *flags |= 0x10u;
   object = object->next;
  }
 }
 while (horizontal > 0) {
  horizontal -= 2;
  vertical -= 2;
  REG16(0x0400004C) = (vertical << 12) | (horizontal << 8)
      | (vertical << 4) | horizontal;
  REG16(0x04000054) = horizontal;
  frame_request_refresh();
  display_step_backgrounds();
  display_step_palette_jobs();
  frame_prepare_oam_transfer();
  irq_wait_vblank();
  irq_wait_vblank();
 }
 if (display & 0x1000) {
  object = g_frame_primary_list.first;
  if (object) {
   unsigned int clear_mask = ~0x10u;
   do {
    unsigned char *flags = (unsigned char *)object + 0xD1;
    *flags &= clear_mask;
    object = object->next;
   } while (object);
  }
 }
}
