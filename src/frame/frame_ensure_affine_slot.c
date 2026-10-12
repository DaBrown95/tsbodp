#include "frame_affine.h"
FrameU32 frame_ensure_affine_slot(struct FrameAffineObject *object)
{
 FrameU16 slot;
 if (object->display.display_mode == 1 || object->display.display_mode == 3)
  slot = frame_get_affine_slot(&object->display);
 else { slot = frame_allocate_affine_slot(); frame_set_affine_slot(&object->display, slot); }
 return slot;
}
