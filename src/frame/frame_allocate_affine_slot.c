#include "frame_affine.h"
FrameU32 frame_allocate_affine_slot(void)
{
 FrameU16 slot=0, remaining=32;
 while (remaining) {
  if (g_frame_affine_slots[slot] != 1) {
   g_frame_affine_slots[slot] = 1;
   if (slot >= g_frame_affine_slot_count) g_frame_affine_slot_count++;
   break;
  }
  slot++; remaining--;
 }
 return slot;
}
