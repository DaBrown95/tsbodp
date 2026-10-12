#include "frame_affine.h"
void frame_free_affine_slot(FrameU16 slot)
{
 g_frame_affine_slots[slot] = 0;
 if (slot == g_frame_affine_slot_count - 1 && g_frame_affine_slot_count) {
  do {
   g_frame_affine_slot_count--;
   slot--;
  } while (g_frame_affine_slot_count && !g_frame_affine_slots[slot]);
 }
}
