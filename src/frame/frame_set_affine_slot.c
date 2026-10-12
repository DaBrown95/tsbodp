#include "frame_affine.h"
void frame_set_affine_slot(struct FrameOam *oam, FrameU16 slot)
{
 struct FrameAffineSlotFields *fields = (struct FrameAffineSlotFields *)oam;
 fields->attr_x = (fields->attr_x & 0xc1ff) | (slot << 9);
}
