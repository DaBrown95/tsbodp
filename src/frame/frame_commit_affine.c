#include "frame_affine.h"
void frame_commit_affine(void)
{
 if (g_frame_affine_slot_count) {
  frame_write_affine_matrices(g_frame_affine_parameters,g_oam_previous+6,g_frame_affine_slot_count,8);
  frame_write_affine_matrices(g_frame_affine_parameters,g_oam_previous+0x406,g_frame_affine_slot_count,8);
 }
}
