#include "frame_affine.h"
FrameU32 frame_get_affine_slot(struct FrameOam *oam)
{
 struct FrameAffineSlotFields *fields = (struct FrameAffineSlotFields *)oam;
 return 31 & (fields->attr_x >> 9);
}
asm(".align 2, 0");
