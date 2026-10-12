#include "frame_indicator.h"
void frame_acquire_palette_slot(struct FrameObject *base, int slot)
{
 struct FrameActorObject *object=(struct FrameActorObject *)base;
 object->oam.palette=slot;
 g_frame_palette_slots[slot].users++;
 object->flags |= 0x08000000;
}
